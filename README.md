# Portfolio 모음

## Evolution Project
해당 프로젝트의 이름을 Evolution으로 정한 이유는 제가 한 단계 더 진화하길 원했기 때문입니다.

이 프로젝트는 고등학교 2학년때부터 고등학교 3학년 1학기까지 제가 Direct X를 공부하면서 만든 게임 개발 기초프레임워크 입니다.

### EvolutionCore
> 해당 프로젝트에서 제일 핵심이 되는 코드는 EvolutionCore입니다.
> Core는 DirectX사용에 필요한 초기화 및 Window응용프로그램의 초기화 및 전체적인 게임의 구조를 잡아줍니다.
> 게임의 구조는 크게 Update와 Render로 구성했습니다.

### EvolutionScene
> EvolutionCore를 통해서 초기화가 끝난다면 다음으로 중요한 것은 EvolutionScene입니다. 해당 클래스는 게임의 화면을 의미합니다. 이 프레임워크를 사용해서 게임을 만든다면 EvolutionScene을 상속받아서 게임 화면을 구성하게 됩니다.
> 그리고 Scene에서 사용되는 객체의 관리를 위해서 Scene에서는 객체관리를 위한 리스트를 보유하고 있습니다.
> 이 리스트에 등록된 객체들은 한번에 Update, Render를 할 수 있습니다. 따로 다른 시점에 Update를 해야하거나 Render를 해야한다면 해당 리스트에서 꺼내면 됩니다.

### EvolutionSceneManager
> 이 클래스는 전체 게임의 Scene을 관리해주는 클래스로 등록된 Scene의 Update, Render를 수행하고 Scene사이의 전환을 담당합니다.

### EvolutionCamera
> Scene까지 생성했다면 이제 장면을 보기 위한 카메라가 필요합니다. EvolutionCamera클래스를 이용해서 카메라를 생성할 수 있습니다.
> 해당 클래스에는 카메라의 위치조정 함수, 회전조정 함수, 지점보간이동 함수를 제공하여 간단한 카메라 액션을 만들어낼 수 있습니다.

### EvolutionShader
> 3D 객체 Rendering에 사용되는 쉐이더를 불러오고 쉐이더에 작성된 Path를 수행하는 기능을 가진 기본 클래스입니다.

### EvolutionTextureManager
> 3D 렌더링에 사용되거나 Effect를 만들어내기 위해 사용되는 Texture들을 효율적으로 관리하기 위한 클래스입니다.
> 
### EvolutionSkyBox
> 3D 공간을 감싸는 거대한 상자 또는 구형 하늘을 구현하는 객체입니다. 이 객체는 카메라와 동일하게 움직여서 무한한 공간상에 배경텍스쳐를 덧입혀주는 역할을 합니다.

### EvolutionGameObject, EvolutionGameObject2D
> 해당 프레임워크에서 사용되는 객체의 기본단위가 되는 클래스입니다. EvolutionGameObject는 3D 객체, EvolutionGameObject2D는 2D 이미지 객체를 뜻합니다.
> 각각의 클래스는 가장 기본이 되는 정보(위치, 각도, 스케일, 회전중심점, 스케일중심점, 로컬좌표계 축 방향 등)를 포함하며 기본적인 이동, 회전, 스케일 변환을 제공합니다.
> 또한 부모자식 계층구조를 이용한 상대좌표,절대좌표 구현을 위해 자식 객체를 관리할 수 있는 리스트를 가지고 있습니다.

### EvolutionShape
> 3D 기본도형 육면체, 구, 원기둥 모델 객체를 생성하는 클래스입니다. 기본적으로 EvolutionGameObject를 상속하여 구현됩니다.

### EvolutionModel
> 제일 기본이 되는 정적인 3D 모델 파일을 불러와서 객체로 생성하는 클래스입니다. 이 객체는 기본적으로 EvolutionGameObject를 상속하여 구현됩니다.
> Direct X에서 지원하는 Mesh, Texture, Material로 구현됩니다.

### EvolutionSprite2D
> 제일 기본이 되는 2D 이미지 파일을 불러와서 객체로 생성하는 클래스입니다. 이 객체는 기본적으로 EvolutionGameObject2D를 상속하여 구현됩니다. 직교투영방식을 사용하여 원근감이 없습니다.
> 2D 게임을 제작하는데 사용할 수 있으며, 3D 게임 제작시 UI를 구성할 때 사용할 수 있습니다.

### EvolutionAnimationModel
> 동적인 애니메이션을 가진 3D 모델 파일을 불러와서 객체로 생성하는 클래스입니다. 이 객체는 기본적으로 EvolutionSkinningModel을 상속하여 구현됩니다.
> EvolutionSkinningModel은 EvolutionAnimationHierarchy, EvolutionDiffuseSkinning의 객체를 사용하여 구현됩니다.
> EvoultionAnimationHierarchy를 통해서 모델 파일을 불러오면서 뼈대의 계층구조를 구성하고, 애니메이션 정보를 토대로 애니메이션 컨트롤러를 구성합니다.
> 또한 각 프레임별 변환행렬들을 계산합니다.
> EvolutionDiffuseSkinning객체는 Diffuse쉐이더를 Skinning 기법에 맞게 수정한 쉐이더 객체입니다. 이를 이용해서 Render를 진행합니다.

### EvolutionTime, EvolutionLog, EvolutionConsole, EvolutionInput, EvolutionMath, EvolutionUIFont
> EvolutionTime은 프레임간 경과시간 및 FPS출력을 담당하는 클래스입니다.

> EvolutionLog는 Win32 Api를 이용해서 제작된 로깅을 위한 클래스입니다.

> EvolutionConsole은 EvolutionLog를 만들기 이전 디버깅이나 로깅을 위해 사용했던 Console을 띄워주는 클래스입니다.

> EvolutionInput은 키보드와 마우스에 관련된 액션을 감지하고, 마우스의 위치정보를 얻기 위한 클래스입니다.

> EvolutionMath는 3D 연산을 위한 여러 수학함수를 구현하기 위해 제작한 클래스입니다.

> EvolutionUIFont는 EvolutionSprite2D와 동일한 메커니즘이지만 글자를 출력하기 위한 클래스로 따로 제작하였습니다.
---
## The Stealth
해당 프로젝트는 위의 Evolution Project로 제작한 프레임워크에서 프레임워크에서 필요하지 않거나 불필요했던 코드들을 수정한 후 진행한 프로젝트입니다.

프로젝트의 목적은 고등학교 2학년 시절 교내대회 출전을 위함이였습니다.

같이 교내대회 출전을 하는 팀원의 요청으로 Direct X 11로 버전을 올려 새로 구현하려다가 많은 문제로 인해 다시 원래 쓰던 9 버전으로 제작된 Evolution Project 프레임워크를 수정하여 진행했습니다.

해당 과정에서 시간낭비를 많이하여 대략 14일의 시간동안 급하게 만들어서 제대로 된 완성을 하지 못했습니다.

제가 이 프로젝트에서 맡은 부분은 기존의 Evolution Project 프레임워크 코드의 수정 및 보완, 게임을 구성하는 GameScene의 기본적인 UI를 프로그래밍하는 것, 구현된 서버와 통신하는 코드를 작성하는 것이였습니다.   
또한 제 파트가 끝난 후 실질적인 게임 동작 파트의 구현에도 힘을 실어주었습니다.   
그러나 앞서 시간낭비와 더불어 3D공간상에서 여러 인터렉션을 구현하는데 있어 능력의 한계에 부딪혀 역부족이였으나, 남들이 하지않는 분야에 대한 개척에 노력을 인정받아 동상을 수상했습니다.   

소스코드와 더불어 아래의 유튜브 링크를 통해서 간단한 UI 프로그래밍 구현 내용을 확인해 보실 수 있습니다.

유튜브 링크 : <https://youtu.be/9uEpybwG0Qc>   
---
## Grand Thief
해당 프로젝트는 위 두 개의 프로젝트를 진행하기 전 고등학교 1학년 시절 처음으로 제작한 캐주얼 퍼즐 장르의 게임프로젝트입니다.

프로젝트의 목적은 교내대회 출전을 위함이였고, 개발에 사용된 언어는 C++입니다. 추가적으로 Sound 라이브러리인 Fmod와 Graphic 라이브러리인 Direct X 9을 사용했습니다.

프로젝트에서 저는 게임 개발에 기반이 되는 Framework를 제작하고 플레이어와 관련된 코드를 작업했습니다. 

고등학교의 방학 때 소수인원을 대상으로 진행하는 특별수업과정에서 게임 개발의 기초를 배우고, 배운 내용을 적용하여 만든 첫 게임입니다.   
그리고 처음 만든 게임이라 제대로 작동하지 못하는 부분도 있고, 최적화에도 문제가 있으나, 대회 출전에 의미를 두고 최대한 완성하려고 노력했던 기억이 납니다.   
그래서 지금와서 보면 코드가 미흡한 부분이 많지만, 게임 개발에 흥미를 붙일 수 있도록 해준 프로젝트이며,   
포트폴리오를 정리하면서 해당 코드를 훑어보며 프로그래밍적 관점이 발전 했음을 느끼게도 해준 프로젝트입니다.   

유튜브 링크 : <https://youtu.be/dVDqOES-ixM>   
---
## Endless Shooting
해당 프로젝트는 대학교 2학년 재학 중에 진행한 슈팅게임 프로젝트입니다.

프로젝트의 목적은 심화프로그래밍(C++강의)에서 배운 내용을 적용하여 하나의 간단한 게임을 만드는 것입니다.

사용한 언어는 C++, Graphic은 OpenGL, Sound는 Fmod 라이브러리를 사용하여 진행하였습니다.   
진행에 있어 특이점은 교수님이 학생들에게 외부 이미지 파일을 사용하지 말고 제작할 것을 요구하셔서 도트시스템을 따로 제작하여 이미지를 사용한 듯한 느낌을 주었습니다.   

게임은 간단하게 구성했습니다. 상하좌우 4방향에서 적이 등장하며, 플레이어는 체력이 다할 때 까지 적기를 격추하는 게임입니다.   
시간이 갈 수록 적기의 등장 주기가 빨라지며, 피격시 2초 무적이 있습니다. 플레이어의 이동은 마우스 커서의 위치로 머리를 돌려 전진하도록 설계했습니다.   

담백하게 필요한 기능만 구현하여 허전한 느낌이 있지만, 외부 에셋 제약이 없다면 조금 더 풍성하게 만들 수 있겠다는 생각도 했습니다.

유튜브 링크 : <https://youtu.be/a8mvkVk7JJ4>   
---
## Keyword-On
해당 프로젝트는 대학교 4학년 졸업 필수과목인 종합설계 강의에서 진행한 웹 서비스 프로젝트입니다.

해당 프로젝트의 목적은 강의에서 배운 설계 방법을 프로젝트에 적용하고 직접 설계한 서비스를 구현까지 해보는 것이 목적입니다.

저는 프로젝트에서 Frontend를 맡아 진행했습니다. 이 프로젝트를 진행하기 위해 웹 개발 지식이 전무한 저는 React.js와 node.js의 사용법을 공부하며 프로젝트를 진행했습니다.   
처음 접하는 생소한 내용이라 중간 중간 고난이 있었는데 첫번째 고난은 레이아웃을 잡는 것에 있었습니다.   
그래서 우선 각 페이지의 레이아웃을 어떻게 구성할 지 설계하고 html로 구현을 해보며 해당 내용을 공부하며 구현해나갔습니다.   
구현 된 레이아웃을 토대로 React.js를 이용하여 서비스를 구현할 때는 각 페이지에 어떤 컴포넌트가 필요한지 생각하면서   
컴포넌트를 구현하여 하나의 페이지에서 조립하여 구성했습니다. 이 부분은 게임프로그래밍에서의 방법과 유사하여 큰 어려움을 겪진 않았습니다.   
그러나 반복되는 코드나 유사한 기능을 수행하는 컴포넌트에 대한 처리가 매우 미숙함을 느꼈고, 앞으로 웹 개발을 진행하려면 해당 사항들을 어떻게 효율적으로 해결해야하는지가 숙제라고 느꼈습니다.   

이 프로젝트의 내용을 간단히 설명하면, 사용자가 궁금한 키워드를 입력하면 해당 키워드에 대한 인터넷 뉴스기사들에서 감정을 분석하고,   
분석 결과와 더불어 여론은 해당 키워드에 대해서 어떻게 생각하는지 알 수 있도록 여러가지 정보를 제공하는 서비스입니다.   

지금와서 생각해보면 이런 서비스는 상당히 민감한 주제이기도 하고, backend에서 사용된 ai모델의 사용이 미숙한 점을 고려하면,   
다른 좋은 주제를 선정하여 프로젝트를 진행 할 수 있었다면 더 좋은 경험이 될 수 있었을 것 같아 아쉬움이 남습니다.   

유튜브 링크 : <https://youtu.be/nL4gH5Lgdu8>   
github 링크 : <https://github.com/CSID-DGU/2023-02-CECD2-4/tree/frontend>   