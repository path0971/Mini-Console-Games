#include <stdio.h>
#include <time.h>
#include "minigame_util.h"
// 10 마리의 서로 다른 동물(각 카드 2장씩)
// 사용자로부터 2개의 입력값을 받아 같은 동물 찾으면 카드 뒤집기
// 모든 동물 쌍을 찾으면 게임 종료
// 총 실패 횟수 알려주기


int main() {

	srand(time(NULL));

	initAnimalArray();
	initAnimalName();

	shuffleAnimal(); // 지도에다가 랜덤으로 동물 배치

	int failCount = 0; // 실패 횟수

	while (1) {
		int select1 = 0;
		int select2 = 0;
		
		printAnimals(); // 동물 위치 출력
		printQuestion(); // 문제 출력(카드 지도)
		printf("뒤집을 카드를 2개 고르세요: ");
		scanf_s("%d %d", &select1, &select2);

		if (select1 == select2) { // 같은 카드를 선택 시 무효!
			continue;
		}

		// 좌표에 해당하는 카드를 뒤집어보고 같은 지 여부 확인
		int firstSelect_x = conv_pos_x(select1);
		int firstSelect_y = conv_pos_y(select1);

		int secondSelect_x = conv_pos_x(select2);
		int secondSelect_y = conv_pos_y(select2);

		// 같은 동물인 경우
		if ((checkAnimal[firstSelect_x][firstSelect_y] == 0
			&& checkAnimal[secondSelect_x][secondSelect_y] == 0)
			&&
			(arrayAnimal[firstSelect_x][firstSelect_y] == 0
			&& arrayAnimal[secondSelect_x][secondSelect_y] == 0)) {

			printf("\n\n 가챠! %s 발견\n\n", strAnimal[firstSelect_x][firstSelect_y]);
			checkAnimal[firstSelect_x][firstSelect_y] = 1;
			checkAnimal[secondSelect_x][secondSelect_y] = 1;
		}

		// 다른 동물인 경우
		else {
			printf("\n\n 틀렸맨! (틀린거나 이미 뒤집힌 걸 골랐다맨)\n");
			printf("%d: %s\n", select1, strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
			printf("%d: %s\n", select2, strAnimal[arrayAnimal[secondSelect_x][secondSelect_y]]);
			printf("\n\n");

			failCount++;
		}

		// 모든 동물 다 찾았는 지 여부
		if (foundAllAnimals() == 1) {
			printf("\n\n끝났다맨!\n");
			printf("지금까지 %d 번 틀렸다맨\n", failCount);
			break;
		}

	}

	return 0;
}

void initAnimalArray() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			arrayAnimal[i][j] = -1; // -1로 초기화 (카드가 뒤집히지 않은 상태)
		}
	}
}

void initAnimalName() {
	strAnimal[0] = "원숭이";
	strAnimal[1] = "강아지";
	strAnimal[2] = "코끼리";
	strAnimal[3] = "사자";
	strAnimal[4] = "돼지";
	strAnimal[5] = "타조";
	strAnimal[6] = "고양이";
	strAnimal[7] = "팬더";
	strAnimal[8] = "캥거루";
	strAnimal[9] = "호랑이";
}

void shuffleAnimal() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			int pos = getEmptyPosition();
			int x = conv_pos_x(pos);
			int y = conv_pos_y(pos);


			arrayAnimal[x][y] = i; // i번째 동물을 빈 위치에 배치
		}
	}
}

// 좌표에서 빈 공간 찾기	
int getEmptyPosition() {
	while (1) {
		int randPos = rand() % 20; // 0 ~ 19
		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (arrayAnimal[x][y] == -1) { // 빈 공간이면
			return randPos; // 위치 반환
		}
	}

	return 0;
}


// 19가 나오면 (3,4)로 x,y 변환이 필요함ㅇㅇ
int conv_pos_x(int x) {
	return x / 5;
}

int conv_pos_y(int y) {
	return y % 5;
}


void printAnimals() { // 나중에 정답 확인용 동물 위치 출력
	printf("\n========히밋츠데스=========\n\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%8s", strAnimal[arrayAnimal[i][j]]);
		}
		printf("\n");
	}
	printf("\n=================\n\n");
}

void printQuestion() {
	printf("\n\n(문제)\n");
	int seq = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			// 카드를 뒤집어서 정답을 맞췄으면 "동물 이름"
			if (checkAnimal[i][j] != 0) {
				printf("%8s", strAnimal[arrayAnimal[i][j]]);
			}
			// 정답을 못맞췄어? 그러면 뒷면 --> 위치를 나타내는 숫자
			else {
				printf("%8d", seq);
			}
			seq++;
		}
		printf("\n");
	}
}


int foundAllAnimals() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (checkAnimal[i][j] == 0) return 0;
		}
	}
	return 1;
}