#ifndef STACK_HPP
# define STACK_HPP

class stack
{
private:
	/* data */
public:
	stack();
	stack(stack const &s);
	stack& operator=(stack const &s);
	~stack();
};

#endif