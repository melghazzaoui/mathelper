//
// Created by Makram.Elghazzaoui on 06/04/2023.
//

#ifndef TEST_SVMODULEGENERATOR_H
#define TEST_SVMODULEGENERATOR_H


#include <cstddef>
#include <ostream>

class SvModuleGenerator {
private:
    std::string moduleName;
    size_t parametersCount;
    size_t portsCount;
    size_t packedDimensions;
    size_t unpackedDimensions;

    int paramDefaultValue;

private:
    void printParameterName(std::ostream& os, int i) const;
    void declareParameter(std::ostream& os, int i) const;
    void declareParameters(std::ostream& os) const;
    void declarePort(std::ostream& os, int i) const;
    void declarePorts(std::ostream& os) const;
    void declareDimension(std::ostream& os, int i) const;
    void declareDimensions(std::ostream& os, size_t dim, int paramIndex) const;

    static std::string PARAM_PREFIX;
    static std::string PORT_PREFIX;

public:
    SvModuleGenerator(std::string  moduleName, size_t parametersCount, size_t portsCount, size_t packedDimensions, size_t unpackedDimensions)
    :   moduleName(moduleName),
        parametersCount(parametersCount),
        portsCount(portsCount),
        packedDimensions(packedDimensions),
        unpackedDimensions(unpackedDimensions),
        paramDefaultValue(16) {

    };

    friend std::ostream& operator << (std::ostream& os, const SvModuleGenerator& svModGen);

};


#endif //TEST_SVMODULEGENERATOR_H
