# page 0

ft_containers
참 쉬워요, C++ 컨테이너!

요약 : C++ 에서 이용할 수 있는 여러 종류의 컨테이너들은 각기 다른 사용법이 있습니다. 이 모든 것들을 직접 한번 재구현해보면서 정말로 이해하고 있는지 확인해봅시다!

# page 1

목차
| Chapter | Contents | Page |
|:---:|:---|:---:|
| I | [__일반적인 규칙__]() | 2 |
| II | [__목표__]() | 4 |
| III | [__필수 파트__]() |  5 |
| IV | [__보너스 파트__]() |  6 |

# page 2
Chapter 1
General rules : 규칙

* 함수가 헤더에 구현된 경우 (템플릿 함수는 제외) 그리고 헤더가 unprotected 인 경우 모두 0점 처리됩니다.
* 클래스이름, 함수이름, 메소드 이름처럼 파일 이름도 반드시 과제에 제시된 이름과 같아야 합니다.
* 명심하세요. 여러분은 더 이상 C가 아니라 C++ 을 하고 있습니다. 그러므로,
	* alloc, printf, free 함수들은 절.대.금.지 이며, 사용할 경우 변명의 여지없이 0점입니다. 
	* 여러분은 standard library 에 있는 모든 것들을 사용할 수 있습니다. 그.러.나 여러분이 알고 있던 것을 고집하기 보다는 C에서 사용하던 함수의 c++ 버전을 사용하는 것이 현명할 것입니다. 어쨌든 이건 결국 새로운 언어니까요.
	* 이 프로젝트에서 여러분의 목표는 STL library 를 재구현하는 것이므로,  구현된 STL 컨테이너를 사용하는 것은 당연히 금지됩니다.
* 명시적으로 금지된 함수나 방법을 사용하는 것은 0점을 맞을 것입니다. 
* 따로 언급하지 않으면 C++ 키워드 중 "using namespace" 와 "friend" 는 사용할 수 없습니다. 만약 어길시 -42점을 맞을 것입니다. 
* class와 관련이 있는 파일은 따로 언급이 없으면 항상 ClassName.hpp 그리고 ClassName.cpp 로 명명되어야 합니다. 
* 예제를 철저하게 정독하세요. 문제에서 명확하지 않던 요구사항이 포함되어 있을 수 있습니다. 만약 애매하게 보인다면 그건 여러분이 C++을 충분히 이해하지 못해서 그런 겁니다.
* C++11, Boost, 프로그래밍을 잘하는 친구가 좋다고 추천한 툴들을 포함한 그 어떤 외부 라이브러리도 사용할 수 없습니다. 
*  여러분들은 아마 상당한 양의 클래스들을 제출해야할 것입니다. 자주 사용하는 텍스트 편집기의 스크립트 기능을 쓰지 않는다면 이러한 과정이 지루하게 느껴질 수도 있습니다.

# page 3

* 프로젝트를 시작하기 전에 주제를 전.부. 읽으세요! 정말로 그렇게 해야합니다.
* 사용해야하는 컴파일러는 clang++ 입니다.
* 여러분의 코드는 반드시 다음과 같은 플래그를 이용해서 컴파일 해야합니다 : -Wall -Wextra -Werror
* 각 `include` 들은 반드시 다른 것으로 부터 독립적으로 포함될 수 있어야합니다. `include` 들은 명백히 의존성이 있는 모든 것들을  포함해야 합니다. 
* 혹시 궁금해할까봐 말씀드리는데, C++ 에서는 어떤 코딩 스타일도 강요하지 않습니다. 여러분은 원하는 코딩 스타일로 제한없이 작성할 수 있습니다. 그러나 여러분의 동료 채점자가 읽을 수 없는 코드는 채점도 할 수 없다는 것을 기억하세요.
* 여기서 중요한 거 한 가지! 여러분의 과제를 프로그램이 채점하지 않을 겁니다. 그렇기에 여러분에게는 과제를 할 때 어떻게 할지 어느정도 선택할 수 있는 자유가 주어집니다. 그러나 각각의 문제에서의 제약사항을 유념하고, 절.대! 게으름피우지마세요. 여러분은 문제가 주는 많은 것들을 놓칠지도 몰라요!
* 문제가 요구한 사항보다 여러분의 코드를 나눠서 더 많은 파일들로 제출하는 것은 상관 없습니다. 프로그램이 채점하는게 아니므로 편하게 하세요.
* 주제에 있는 문제가 짧아도, 해당 문제가 여러분에게 요구하는게 무엇인지, 그리고 최선의 방법으로 문제를 해결했는지 충분한 시간을 갖고 풀어보세요. 그럴만한 가치가 있습니다.

# page 4
Objectives 목표

이 프로젝트에서 여러분은 다양한 C++ standard template library 컨테이너 타입을 구현할 것입니다. 각각의 컨테이너를 구현하기 위해, 적절한 class 파일들 이름을 설정해서 제출해주세요. `namespace` 는 항상 `ft` 이며 컨테이너 테스트를 `ft::<container>` 형태로 할 것입니다. 각각의 class 는 반드시 Coplien form 이어야 합니다. 재차 말하지만, 우리는 C++98 버전으로 코드를 작성하므로 반.드.시 해당 버전 이후의 새로운 기능들은 구현하지 말아야 하고, 반대로 오래되거나 사라질 예정인 기능들은 C++98 이라면 반드시 구현해야합니다. 

# page 5
Mandatory part 필수 사항

* 다음의 컨테이너들을 `<container>.hpp` 에 구현하여 제출하세요.
* 여러분은 반드시 평가시 테스트에 사용할 `main.cpp` 도 같이 제공해야합니다.
* 멤버 함수, 비멤버 함수, 오버로드를 모두 구현해야 합니다.
* `get_allocator` 맴버 함수를 구현하지 않아도 된다면, `std::allocator` 을 사용할 수 있습니다.
* 각각의 컨테이너에 사용된 내부 데이터 구조의 당위성을 반드시 설명할 수 있어야 하며, 맵 컨테이너에 단순히 배열을 사용한 것은 허용되지 않습니다.
* 만약 컨테이너가 iterator 를 가지고 있다면 반드시 재구현해야합니다.
* 해당 사이트 [cplusplus.com](https://www.cplusplus.com/) 에서 구현해야 하는 C++98 버전을 참고하실 수 있습니다.
* [cppreference.com](https://www.cppreference.com/) 는 최신 버전에 조금 더 정확합니다.
* standard 컨테이너가 가진 `public` 함수보다 더 많은 `public` 함수를 구현할 수 없습니다. 그 외의 것들은 `private` 이나 `protected` 이어야 합니다. 각 `public` 함수/변수들은 반드시 정당한 방식으로 사용되어야 합니다.
* non-member overloads 에 한해서 `friend` 키워드가 용인됩니다. 모든 `friend` 의 사용은 정당한 방식으로 사용되어야 하며, 채점시에 채점자가 확인할 것입니다.  

여러분은 반드시 다음의 컨테이너들과 그 안의 함수들을 구현하여 제출해야합니다.
* List
* Vector
* Map
* Stack
* Queue

물론 STL 의 사용은 금지입니다. 그러나 STD library 는 사용 가능합니다. 

# page6
Bonus part 보너스

여러분이 앞에서 필수사항을 완전히 끝냈다면, 추가로 파일을 제출해 보너스를 받을 수 있습니다.

보너스를 받기 위해 다음의 컨테이너들과 그 안의 함수들을 구현하여 제출해야합니다. 
* Deque
* Set
* Multiset
* Multimap
