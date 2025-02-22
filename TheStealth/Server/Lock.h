#pragma once

class Lock
{
private:
	lock_t          mutex_;
	wstr_t			name_;
	size_t          lockId_;
	size_t			threadId_;

	wstr_t			lockingFile_;
	int				lockingLine_;

public:
	Lock(WCHAR* name);
	virtual ~Lock();

	const WCHAR* name();
	size_t lockId();

	lock_t& mutex();
	void lock(wstr_t fileName, int lineNo);
	void unlock();

	void setThreadId(size_t id);
	size_t threadId();
};

class LockSafeScope
{
	Lock          *lock_;
public:
	LockSafeScope(Lock *lock, LPCWSTR fileName, int lineNo);
	~LockSafeScope();
};

#define SAFE_LOCK(lock)     LockSafeScope __lockSafeScope(&lock, _W(__FILE__), __LINE__);

// 데드락 탐지를 위함
class LockManager : public Singleton < LockManager >
{
	size_t       idSeed_;

public:
	LockManager();

	Lock* searchLockCycle(Lock *newLock);
	Lock* checkDeadLock(Lock *lock);

	size_t generalId();
};
