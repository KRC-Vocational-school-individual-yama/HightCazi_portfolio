#include"object.h"
#include<DxLib.h>
#include"string"
using namespace std;


namespace {
	int winNum = 0;
	bool loosFlag = false;
	const int ENEMISNUM = 3;

	int mousex = 0,
		mousey = 0;
	bool kurikkuflag = false;

	struct Circle {
		double x,
			y,
			r;
		int myColor = 0;
	};
	Circle playerCircle;
	Circle enemisCircle[ENEMISNUM];

	string playerfomat = "";
	string enemisfomat[ENEMISNUM] = {};

	int plauerStrNum = 3;
	int enemisStrNum[ENEMISNUM] = {};

	bool deleteFlag[ENEMISNUM] = {};
	int counter[ENEMISNUM] = {};
}
bool Circlecollition(Circle pla,Circle ene) {
	int mx=pla.x,
		my=pla.y,
		mr=pla.r;
	int ex=ene.x,
		ey=ene.y,
		er=ene.r;
	int nX = mx - ex;
	int nY = my - ey;
	int radius = mr + er;
	bool flag = nX * nX + nY * nY < radius* radius;
	if (flag)return true;
	return false;
}

void Init() {
	plauerStrNum = GetRand(3)+3;
	playerCircle.x = 100;
	playerCircle.y = 250;
	playerCircle.r = 20;
	playerCircle.myColor = GetColor(0xe8, 0x52, 0x98);
	playerfomat=to_string(plauerStrNum);
	
	for (int i = 0; i < ENEMISNUM; i++) {
		enemisCircle[i].x = 400;
		enemisCircle[i].y = 100+(i * 150);
		enemisCircle[i].r = 20;
		enemisStrNum[i] = GetRand(10+winNum)+1;
		enemisfomat[i]=to_string(enemisStrNum[i]);
		deleteFlag[i] = false;
	}

}
void Update() {
	if(!loosFlag){
	for (int i = 0; i < ENEMISNUM; i++) {
	counter[i]++;
	}

	GetMousePoint(&mousex,&mousey);
	bool mousehitkey = GetMouseInput() & MOUSE_INPUT_LEFT;
	if (kurikkuflag) {
		playerCircle.x = mousex;
		playerCircle.y = mousey;
	}
	else {
		playerCircle.x = 100;
		playerCircle.y = 250;
	}

		
	bool enemyflag[ENEMISNUM];
		enemyflag[0] = Circlecollition(playerCircle, enemisCircle[0]);
		enemyflag[1] = Circlecollition(playerCircle, enemisCircle[1]);
		enemyflag[2] = Circlecollition(playerCircle, enemisCircle[2]);
		for (int i = 0; i < ENEMISNUM; i++) {
			if (!deleteFlag[i]) {
				if (enemyflag[i]) {
					if (!mousehitkey) {
						bool tasuflag = enemisStrNum[i] < plauerStrNum;
						if (tasuflag) {
							plauerStrNum += enemisStrNum[i];
							deleteFlag[i] = true;
							counter[i] = 0;
							break;
						}
						else {
							loosFlag = true;
							//return 1;
						}
					}
				}
			}
		}






	Circle mou = {mousex,mousey,2};
	bool myflag=Circlecollition(mou,playerCircle);
	if (myflag) {
		playerCircle.myColor = GetColor(100,100,255);
		
		kurikkuflag= mousehitkey ? true : false;
	}
	else {
		playerCircle.myColor = GetColor(0xe8, 0x52, 0x98);
	}

	for (int i = 0; i < ENEMISNUM; i++) {
		enemisfomat[i] = to_string(enemisStrNum[i]);
		playerfomat = to_string(plauerStrNum);

		if (deleteFlag[i]&&counter[i]>60) {
			enemisStrNum[i] = GetRand(10) + 1;
			deleteFlag[i] = false;
		}
	}
	
}}
void Draw() {
	//printfDx("%d",winNum);
	DrawCircle(playerCircle.x,playerCircle.y,playerCircle.r,playerCircle.myColor,false);
	DrawFormatString(playerCircle.x,playerCircle.y,GetColor(255,255,255),playerfomat.c_str());
	
	int color = GetColor(255,0,0);
	for (int i = 0; i < ENEMISNUM; i++) {
		if (!deleteFlag[i]) {
		DrawCircle(enemisCircle[i].x, enemisCircle[i].y , enemisCircle[i].r, color, false);
		DrawFormatString(enemisCircle[i].x,enemisCircle[i].y,color,enemisfomat[i].c_str());
		}
	}

	if (loosFlag) {
		SetFontSize(100);
		DrawFormatString(100,200,GetColor(255,255,255),"‚ ‚È‚½‚Ì•‰‚¯");
		SetFontSize(16);
		//printfDx("www");
	}
}
void Delete() {

}