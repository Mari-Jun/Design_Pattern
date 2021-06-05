// ISP : (Interface Segregation Principle) 인터페이스 분리 원칙

struct Scene;

struct Mouse
{
	virtual void click(char button) {}
};

struct KeyBoard
{
	virtual void press(char key) {}
};

struct Moniter
{
	virtual void draw(const Scene& scene) {}
};


struct ComputerA
{
	ComputerA(const Moniter& moniter, const KeyBoard& keyboard)
		: moniter{ moniter }
		, keyboard{ keyboard }
	{}

	Moniter moniter;
	KeyBoard keyboard;
};

struct ComputerB
{
	ComputerB(const Moniter& moniter, const Mouse& mouse)
		: moniter{ moniter }
		, mouse{ mouse }
	{}

	Moniter moniter;
	Mouse mouse;
};