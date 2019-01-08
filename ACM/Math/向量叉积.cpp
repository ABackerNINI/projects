struct Point{
	ll x, y;
};

//返回二维向量p1×p2,叉积
inline ll product(const Point &p1, const Point &p2){
	return p1.x*p2.y - p1.y*p2.x;
}



struct Point3D{
	ll x, y, z;
};

//返回三维向量p1×p2,叉积
inline Point3D product(const Point3D &p1, const Point3D &p2){
	Point3D ret;
	ret.x = p1.y*p2.z - p1.z*p2.y;
	ret.y = p1.z*p2.x - p1.x*p2.z;
	ret.z = p1.x*p2.y - p1.y*p2.x;
	return ret;
}