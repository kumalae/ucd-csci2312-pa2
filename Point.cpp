//
// Created by Enoch Kumala on 10/31/2015.
//

#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "Point.h"

namespace Clustering {
    const char Point::POINT_VALUE_DELIM = ',';

    Point::Point(int dims) {
        if (dims != 0) {
            dim = dims;
            values = new double[dim];

            for (int i=0; i<dim; i++)
                values[i] = 0;
        }
    }

    Point::Point(int dims, double *pValues) {
        if (dims != 0) {
            dim = dims;
            values = new double[dim];

            for (int i=0; i<dims; i++)
                values[i] = pValues[i];
        }
    }

    Point::Point(const Point &point) {
        dim = point.dim;
        values = new double[dim];

        for (int i=0; i<dim; i++)
            values[i] = point.values[i];
    }

    Point &Point::operator=(const Point &point) {
        if (this != &point) {
            dim = point.dim;
            values = new double[dim];
            for (int i=0; i<dim; i++)
                values[i] = point.values[i];
        }

        return *this;
    }

    Point::~Point() {
        delete[] values;
    }

    void Point::setValue(int dimension, double value) {
        if (dimension >= 1 && dimension <= dim)
            values[dimension-1] = value;
    }

    double Point::getValue(int dimension) const {
        if (dimension >= 1 && dimension <= dim)
            return values[dimension-1];

        return 0;
    }

    double Point::distanceTo(const Point &point) const {
        if (point.dim == dim) {
            double sum = 0;
            for (int i=0; i<dim; i++)
                sum += pow(values[i] - point.values[i], 2);
            return sqrt(sum);
        }
        return 0;
    }

    Point &Point::operator*=(double d) {
        for (int i=1; i<=dim; i++)
            values[i-1] *= d;

        return *this;
    }

    Point &Point::operator/=(double d) {
        for (int i=1; i<=dim; i++)
            values[i-1] /= d;

        return *this;
    }

    const Point Point::operator*(double d) const {
        Point point(dim);

        for (int i=1; i<=dim; i++)
            point.values[i-1] = values[i-1] * d;

        return point;
    }

    const Point Point::operator/(double d) const {
        Point point(dim);

        for (int i=1; i<=dim; i++)
            point.values[i-1] = values[i-1] / d;

        return point;
    }

    Point &operator+=(Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
            lhs.values[i-1] += rhs.values[i-1];

        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
            lhs.values[i-1] -= rhs.values[i-1];

        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs) {
        Point point(lhs.dim);

        for (int i=1; i<=lhs.dim; i++)
            point.setValue(i, lhs.values[i-1]+rhs.values[i-1]);

        return point;
    }

    const Point operator-(const Point &lhs, const Point &rhs) {
        Point point(lhs.dim);

        for (int i=1; i<=lhs.dim; i++)
            point.setValue(i, lhs.values[i-1]-rhs.values[i-1]);

        return point;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] != rhs.values[i-1])
                return false;
        }
        return true;
    }

    bool operator!=(const Point &lhs, const Point & rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] == rhs.values[i-1])
                return false;
        }
        return true;
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] < rhs.values[i-1])
                return true;
        }
        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] > rhs.values[i-1])
                return true;
        }
        return false;
    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] <= rhs.values[i-1])
                return true;
        }
        return false;
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        for (int i=1; i<=lhs.dim; i++)
        {
            if (lhs.values[i-1] >= rhs.values[i-1])
                return true;
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &stream, const Point &point) {
        for (int i=1; i<point.dim; i++)
            stream << point.values[i-1] << Point::POINT_VALUE_DELIM << " ";
        stream << point.values[point.dim-1];

        return stream;
    }

    std::istream &operator>>(std::istream &stream, Point &point) {
        std::string line, value;
        int i = 1;

        while (getline(stream, value, Point::POINT_VALUE_DELIM))
            point[i++] = strtod(value.c_str(), NULL);

        return stream;
    }
}
