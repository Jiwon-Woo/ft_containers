#ifndef VECTOR_HPP
# define VECTOR_HPP

class vector
{
private:
	/* data */
public:
	vector();
	vector(vector const &v);
	vector& operator=(vector const &v);
	~vector();
};

#endif