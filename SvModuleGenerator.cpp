//
// Created by Makram.Elghazzaoui on 06/04/2023.
//

#include "SvModuleGenerator.h"

std::string SvModuleGenerator::PARAM_PREFIX = "param";
std::string SvModuleGenerator::PORT_PREFIX = "port";

void SvModuleGenerator::printParameterName(std::ostream &os, int i) const {
    os << PARAM_PREFIX << i;
}

void SvModuleGenerator::declareParameter(std::ostream &os, int i) const {
    os << "parameter ";
    printParameterName(os, i);
    os << '=' << paramDefaultValue;
}

void SvModuleGenerator::declareParameters(std::ostream &os) const {
    if (parametersCount > 0) {
        os << std::endl
        << "\t#(" << std::endl;
        for(auto i=0; i< parametersCount; ++i) {
            declareParameter(os, i);
            if (i < parametersCount-1) {
                os << ',';
            }
            os << std::endl;
        }
        os << ')';
    }
}

void SvModuleGenerator::declarePort(std::ostream &os, int i) const {
    os << "input";
    if (packedDimensions > 0) {
        os << ' ';
        declareDimensions(os, packedDimensions, i);
    }
    os << ' ' << PORT_PREFIX << i;
    if (unpackedDimensions) {
        os << ' ';
        declareDimensions(os, unpackedDimensions, i);
    }
}

void SvModuleGenerator::declarePorts(std::ostream &os) const {
    if (portsCount > 0) {
        os << std::endl
           << "(" << std::endl;
        for(auto i=0; i< portsCount; ++i) {
            declarePort(os, i);
            if (i < portsCount-1) {
                os << ',';
            }
            os << std::endl;
        }
        os << ')';
    }
}

void SvModuleGenerator::declareDimension(std::ostream &os, int i) const {
    os << '[';
    printParameterName(os, i);
    os << "-1:0]";
}

void SvModuleGenerator::declareDimensions(std::ostream &os, size_t dim, int paramIndex) const {
    for(auto i=0; i<dim; ++i) {
        declareDimension(os, paramIndex);
    }
}

std::ostream& operator << (std::ostream& os, const SvModuleGenerator& svModGen) {
    os << "module " << svModGen.moduleName;
    svModGen.declareParameters(os);
    svModGen.declarePorts(os);
    os << ';' << std::endl
    << "endmodule" << std::endl;
    return os;
}