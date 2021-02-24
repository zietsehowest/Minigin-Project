#pragma once
#include <iostream>
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};
class FireCommand final : public Command
{
public:
	virtual void Execute() { Fire(); }
private:
	void Fire() { std::cout << "Fire \n"; };
};
class DuckCommand final : public Command
{
public:
	virtual void Execute() { Duck(); }
private:
	void Duck() { std::cout << "Duck \n"; };
};
class JumpCommand final : public Command
{
public:
	virtual void Execute() { Jump(); }
private:
	void Jump() { std::cout << "Jump \n"; };
};
class FartCommand final : public Command
{
public:
	virtual void Execute() { Fart(); }
private:
	void Fart() { std::cout << "Fart \n"; };
};
