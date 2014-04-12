#ifndef QEXCEPTION_HPP
#define QEXCEPTION_HPP

#include <QException>

class QArgumentNullException : public QException
{
public:
	QArgumentNullException() = default;
	QArgumentNullException(const QArgumentNullException&) = default;
	virtual void raise() const final { throw *this; }
	virtual QArgumentNullException* clone() const final { return new QArgumentNullException(*this); }
};

class QArgumentOutOfRangeException : public QException
{
public:
	QArgumentOutOfRangeException() = default;
	QArgumentOutOfRangeException(const QArgumentOutOfRangeException&) = default;
	virtual void raise() const final { throw *this; }
	virtual QArgumentOutOfRangeException* clone() const final { return new QArgumentOutOfRangeException(*this); }
};

#endif // QEXCEPTION_HPP
