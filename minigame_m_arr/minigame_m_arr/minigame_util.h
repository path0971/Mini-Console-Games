int arrayAnimal[4][5]; // 카드 지도 (총 20장)
int checkAnimal[4][5]; // 뒤집힌 여부 확인용 배열!
char* strAnimal[10]; // 동물 이름 배열
void initAnimalArray();
void initAnimalName();
void shuffleAnimal();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAnimals();
void printQuestion();
int foundAllAnimals();