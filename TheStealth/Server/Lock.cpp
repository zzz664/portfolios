#include "DXUT.h"
#include "Thread.h"
#include "Lock.h"
#ifdef _DEBUG
#define STERN_MODE
#endif

const int INVALID_LINE = -1;

Lock::Lock(WCHAR *name)
{
	lockId_ = LockManager::getInstance().generalId();
	name_ = name;

	lockingFile_.clear();
	lockingLine_ = INVALID_LINE;
}

Lock::~Lock()
{
	name_.clear();
}

const WCHAR* Lock::name() 
{
	return name_.c_str();
}

size_t Lock::lockId()
{
	return lockId_;
}

lock_t& Lock::mutex()
{
	return mutex_;
}

void Lock::lock(wstr_t fileName, int lineNo)
{
	mutex_.lock();
	
	lockingFile_ = fileName;
	lockingLine_ = lineNo;
}

void Lock::unlock()
{
	mutex_.unlock();

	lockingFile_.clear();
	lockingLine_ = INVALID_LINE;
}

void Lock::setThreadId(size_t id)
{
	threadId_ = id;
}

size_t Lock::threadId()
{
	return threadId_;
}
//-------------------------------------------------------//
// 생성자에서 락을 걸고, 스코프 빠져나가는 객체 해제시 락을 푼다.
// std::lock_guard<lock_t> guard(lock) 과 같은거지만, 
// 데드락 감지를 위해 직접 구현한다.
LockSafeScope::LockSafeScope(Lock *lock, LPCWSTR fileName, int lineNo)
{
	if (lock == nullptr) {
		return;
	}

	lock_ = lock;
	Lock *deadLock = LockManager::getInstance().checkDeadLock(lock_);
	if (deadLock != nullptr) {
#ifdef STERN_MODE
		//CLog::WriteLog(L"! [%s]lock and [%s]lock is dead detecting!", deadLock->name(), lock->name());
#else
		std::lock(lock_->mutex(), deadLock->mutex());
		//SLog(L"!!! [%s]lock and [%s]lock is dead detecting!", deadLock->name(), lock->name());
#endif
		return;
	}

	lock_->lock(fileName, lineNo);
	lock->setThreadId(GET_CURRENT_THREAD_ID());
}

LockSafeScope::~LockSafeScope()
{
	if (!lock_) {
		return;
	}
	lock_->unlock();
	lock_->setThreadId(0);
}

//-------------------------------------------------------//
LockManager::LockManager()
{
	idSeed_ = 0;
}


Lock* LockManager::searchLockCycle(Lock *newLock)
{
	//list 따라 lock 이름을 비교해 본다.
	Thread *thread = ThreadManager::getInstance().at(GET_CURRENT_THREAD_ID());
	if (!thread) {
		return nullptr;
	}
	std::vector<Lock *> trace;		// 데드락 탐지시, 걸린 락 stact 추척
	trace.push_back(newLock);

	Lock *deadLock = nullptr;
	while (true) {
		Lock *threadLock = thread->lock();
		if (threadLock == nullptr) {
			break;
		}
		if (threadLock->lockId() == trace[0]->lockId()) {
			deadLock = threadLock;
			break;
		}
		trace.push_back(threadLock);
		thread = ThreadManager::getInstance().at(threadLock->threadId());
		if (!thread) {
			break;
		}
	}
	trace.empty();
	return deadLock;
}

Lock* LockManager::checkDeadLock(Lock *newLock)
{
	Lock *deadLock = this->searchLockCycle(newLock);
	if (deadLock) {
		return deadLock;
	}

	return nullptr;
}

size_t LockManager::generalId()
{
	size_t id = idSeed_++;
	return id;
}
