
class randomValue
{
public:
	randomValue( int* source, int nSize );
	~randomValue(void);

	int getRandomValue();
private:
	int* sourceArray;
	int size;
};