
#include "logger.h"

LoggingDecorator::LoggingDecorator(Let &letObj, Logger &loggerObj)
    : letInstance(letObj), logger(loggerObj) {}

LoggingDecorator LoggingDecorator::operator+(const LoggingDecorator &other)
{
    logger.log("Adding two LoggingDecorator objects");
    Let &result = letInstance + other.letInstance;
    return LoggingDecorator(result, logger);
}
LoggingDecorator LoggingDecorator::operator-(const LoggingDecorator &other)
{
    try
    {
        logger.log("Subtracting two LoggingDecorator objects");
        Let &result = letInstance - other.letInstance;
        return LoggingDecorator(result, logger);
    }
    catch (const std::runtime_error &e)
    {
        logger.log(e.what());
        throw;
    }
}

char LoggingDecorator::operator[](const int index)
{
    logger.log("Indexing into a Let object");
    return letInstance[index];
}

std::ostream &operator<<(std::ostream &os, LoggingDecorator &decorator)
{
    decorator.logger.log("Printing a Let object");
    os << decorator.letInstance;
    return os;
}