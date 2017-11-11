class Bird {

private: 
	double x;
	double y;
	double vx;
	double vy;

public:

	Bird();
	Bird(double pos_x, double pos_y, double v_x, double v_y);
	~Bird();

	double getX();
	double getY();
	double getVX();
	double getVY();

	void move(const double dx, const double dy);	
	void print();

};