<div align="center">

# 🎮 Mini Console Games

### C로 만드는 작은 콘솔 게임

**배열 · 난수 · 좌표 변환 · 입력 처리 · 게임 상태 관리**

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Console](https://img.shields.io/badge/Interface-Console-1F2937?style=for-the-badge)
![VisualStudio](https://img.shields.io/badge/Build-Visual_Studio_2022-5C2D91?style=for-the-badge)
![Game](https://img.shields.io/badge/Game-Animal_Pairs-F59E0B?style=for-the-badge)

작은 게임을 통해 C 언어의 자료 표현과 제어 흐름을 익히는 학습 프로젝트입니다.

[게임 소개](#-게임-소개) · [플레이 방법](#-플레이-방법) · [구현 구조](#-구현-구조) · [빌드 방법](#-빌드-방법)

</div>

---

## 🐾 게임 소개

현재 저장소에는 **동물 카드 짝 맞추기** 게임 한 개가 포함되어 있습니다.

4×5 카드판에 10종류의 동물을 두 장씩 배치하고, 사용자가 두 위치를 선택하여 같은 동물의 짝을 찾는 구조입니다. 모든 짝을 찾으면 게임을 종료하고 실패 횟수를 알려주도록 설계되어 있습니다.

> 현재 소스에는 짝 판정과 성공 메시지 출력에 오류가 있습니다. 아래 규칙은 게임의 설계 의도이며, 정상적인 완주를 위해서는 하단의 보완 항목을 먼저 반영해야 합니다.

| 항목 | 구성 |
| --- | --- |
| 카드판 | 4행 × 5열 |
| 전체 카드 | 20장 |
| 동물 종류 | 10종, 각 2장 |
| 선택 번호 | `0`부터 `19`까지 |
| 입력 방식 | 서로 다른 카드 번호 두 개를 공백으로 구분 |
| 목표 | 모든 동물의 짝 찾기 |
| 기록 | 실패 횟수 |

### 등장 동물

🐒 원숭이 · 🐶 강아지 · 🐘 코끼리 · 🦁 사자 · 🐷 돼지  
타조 · 🐱 고양이 · 🐼 팬더 · 🦘 캥거루 · 🐯 호랑이

## 🕹️ 플레이 방법

### 카드 위치

| 행 / 열 | 0열 | 1열 | 2열 | 3열 | 4열 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0행** | 0 | 1 | 2 | 3 | 4 |
| **1행** | 5 | 6 | 7 | 8 | 9 |
| **2행** | 10 | 11 | 12 | 13 | 14 |
| **3행** | 15 | 16 | 17 | 18 | 19 |

화면에서 두 카드의 번호를 골라 입력합니다.

```text
뒤집을 카드를 2개 고르세요: 3 12
```

의도한 게임 진행은 다음과 같습니다.

1. 같은 동물의 카드를 선택하면 두 위치를 찾은 상태로 표시합니다.
2. 다른 동물이거나 이미 찾은 카드를 선택하면 실패 횟수를 증가시킵니다.
3. 같은 번호를 두 번 입력하면 해당 선택을 건너뜁니다.
4. 모든 카드가 찾은 상태가 되면 종료하고 실패 횟수를 출력합니다.

현재는 매 차례 `printAnimals()`가 **전체 정답 배치도 출력**합니다. 정답을 숨기려면 메인 반복문에서 해당 호출을 제외해야 합니다.

## ⚙️ 구현 구조

### 상태를 두 배열로 분리

| 데이터 | 역할 |
| --- | --- |
| `arrayAnimal[4][5]` | 각 카드에 배치된 동물 ID 저장 |
| `checkAnimal[4][5]` | 찾은 카드인지 기록: `0`은 미발견, `1`은 발견 |
| `strAnimal[10]` | 동물 ID에 대응하는 이름 |
| `failCount` | 실패 횟수 |

`arrayAnimal`은 배치 전에 `-1`로 초기화됩니다. `checkAnimal`은 전역 배열이므로 프로그램 시작 시 0으로 초기화됩니다.

### 카드 번호를 좌표로 변환

5열 배열에서 입력 번호를 행과 열로 나눕니다.

```c
int conv_pos_x(int x) {
    return x / 5;
}

int conv_pos_y(int y) {
    return y % 5;
}
```

예를 들어 `19`는 **3행 4열**에 대응합니다. 함수 이름에는 x·y가 사용되지만 배열 접근에서는 각각 첫 번째·두 번째 인덱스입니다.

### 무작위 배치

`shuffleAnimal()`은 동물 ID `0~9`를 순회하며 각각 두 번 빈 위치를 찾아 배치합니다.

- `srand(time(NULL))`로 난수 시드를 설정합니다.
- `rand() % 20`으로 위치를 선택합니다.
- 이미 채워진 위치라면 다시 선택합니다.
- `-1`인 빈 위치를 찾으면 동물 ID를 저장합니다.

### 기능별 함수

| 함수 | 책임 |
| --- | --- |
| `initAnimalArray()` | 배치 배열을 `-1`로 초기화 |
| `initAnimalName()` | 동물 이름 10개 등록 |
| `shuffleAnimal()` | 각 동물을 두 장씩 배치 |
| `getEmptyPosition()` | 무작위 빈 위치 선택 |
| `conv_pos_x()`, `conv_pos_y()` | 번호를 배열 좌표로 변환 |
| `printAnimals()` | 전체 정답 배치 출력 |
| `printQuestion()` | 카드 번호 또는 발견한 동물 이름 출력 |
| `foundAllAnimals()` | 모든 카드의 발견 상태 검사 |

## 🗂️ 저장소 구성

| 파일 | 설명 |
| --- | --- |
| [`minigame_m_arr.sln`](minigame_m_arr/minigame_m_arr.sln) | Visual Studio 솔루션 |
| [`minigame_m_arr.c`](minigame_m_arr/minigame_m_arr/minigame_m_arr.c) | 게임 루프와 함수 구현 |
| [`minigame_util.h`](minigame_m_arr/minigame_m_arr/minigame_util.h) | 전역 배열 및 함수 선언 |
| [`minigame_m_arr.vcxproj`](minigame_m_arr/minigame_m_arr/minigame_m_arr.vcxproj) | Windows 빌드 설정 |

## 🛠️ 빌드 방법

### 준비 환경

- Windows
- Visual Studio 2022
- **C++를 사용한 데스크톱 개발** 워크로드
- MSVC v143 도구 집합 및 Windows SDK

소스 확장자는 `.c`이며, 콘솔 입력에 `scanf_s()`를 사용합니다.

### 저장소 열기

```powershell
git clone https://github.com/path0971/Mini-Console-Games.git
cd Mini-Console-Games
```

1. `minigame_m_arr/minigame_m_arr.sln`을 Visual Studio에서 엽니다.
2. 아래 보완 항목을 확인하여 적용합니다.
3. **Debug / x64** 구성을 선택하고 솔루션을 빌드합니다.
4. `Ctrl + F5`로 실행합니다.
5. `0~19` 범위의 서로 다른 정수 두 개를 입력합니다.

한글 주석과 문자열이 포함된 소스는 기존 CP949 인코딩을 고려해 엽니다. 인코딩을 변경하는 경우 컴파일러와 콘솔 출력 설정도 함께 확인합니다.

## 🔧 현재 코드의 보완 항목

다음은 README 작성 과정에서 소스를 읽고 확인한 내용입니다. 이 문서에서는 게임 소스를 변경하지 않았습니다.

| 항목 | 현재 코드 | 필요한 보완 |
| --- | --- | --- |
| 짝 판정 | 두 카드의 동물 ID가 모두 `0`인지 검사 | 두 ID가 같은지 비교 |
| 성공 메시지 | `strAnimal[firstSelect_x][firstSelect_y]`를 `%s`로 출력 | 동물 ID로 이름 문자열 선택 |
| 표준 헤더 | `rand()`, `srand()` 사용, `<stdlib.h>` 누락 | 헤더 추가 |
| 입력 범위 | 배열 접근 전 `0~19` 검사 없음 | 유효 범위 확인 |
| 입력 형식 | `scanf_s()` 반환값을 확인하지 않음 | 정수 2개 입력 여부 및 실패 시 입력 처리 |
| 정답 노출 | 매 차례 `printAnimals()` 호출 | 게임 모드에서는 숨기거나 디버그 옵션으로 분리 |

짝 판정은 **두 카드가 아직 발견되지 않았다는 조건을 유지하면서** 다음 비교를 사용해야 합니다.

```c
arrayAnimal[firstSelect_x][firstSelect_y]
    == arrayAnimal[secondSelect_x][secondSelect_y]
```

성공 메시지의 동물 이름은 다음 식으로 가져옵니다.

```c
strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]
```

현재 코드는 일반적인 동물 쌍을 정답으로 처리하지 못하고 성공 출력도 잘못되어 있으므로, 완성된 플레이 결과로 소개하지 않습니다. Windows 빌드와 플레이 테스트는 이 README 작성 과정에서 수행하지 않았습니다.

## 🌱 확장 방향

- [ ] 짝 판정과 출력 오류 수정
- [ ] 입력 검증 및 잘못된 입력 복구
- [ ] 정답 표시를 디버그 옵션으로 분리
- [ ] 시도 횟수·경과 시간 기록
- [ ] 카드 수에 따른 난이도 선택
- [ ] 재시작과 게임 선택 메뉴
- [ ] 추가 콘솔 게임 구현

---

<div align="center">

**Mini Console Games**<br>
작은 게임으로 익히는 C 언어의 배열과 상태 관리

</div>
