uint moveByForce(Vector* out,Point* pt,uint weight);
void getForce(Vector* out,const Vector* dis,uint weight);
//void moveByHoming(Vector* source,const Point* pt,const Point* target,uint theta);
/*引き寄せる力関係*/
#define G1 1	//元になる定数
#define G2 256	//元になる定数
