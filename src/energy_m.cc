//
// Generated file, do not edit! Created by nedtool 5.2 from src/energy.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "energy_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EnergyMsg)

EnergyMsg::EnergyMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->source = 0;
    this->destination = 0;
    this->hopCount = 0;
    this->startTimestamp = 0;
    this->endTimestamp = 0;
    this->enqueueTimestamp = 0;
    this->dequeueTimestamp = 0;
    for (unsigned int i=0; i<60; i++)
        this->energyCost[i] = 0;
    this->priority = 0;
}

EnergyMsg::EnergyMsg(const EnergyMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

EnergyMsg::~EnergyMsg()
{
}

EnergyMsg& EnergyMsg::operator=(const EnergyMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void EnergyMsg::copy(const EnergyMsg& other)
{
    this->source = other.source;
    this->destination = other.destination;
    this->hopCount = other.hopCount;
    for (unsigned int i=0; i<60; i++)
        this->timestamp[i] = other.timestamp[i];
    this->startTimestamp = other.startTimestamp;
    this->endTimestamp = other.endTimestamp;
    this->enqueueTimestamp = other.enqueueTimestamp;
    this->dequeueTimestamp = other.dequeueTimestamp;
    for (unsigned int i=0; i<60; i++)
        this->energyCost[i] = other.energyCost[i];
    this->priority = other.priority;
}

void EnergyMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->hopCount);
    doParsimArrayPacking(b,this->timestamp,60);
    doParsimPacking(b,this->startTimestamp);
    doParsimPacking(b,this->endTimestamp);
    doParsimPacking(b,this->enqueueTimestamp);
    doParsimPacking(b,this->dequeueTimestamp);
    doParsimArrayPacking(b,this->energyCost,60);
    doParsimPacking(b,this->priority);
}

void EnergyMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->hopCount);
    doParsimArrayUnpacking(b,this->timestamp,60);
    doParsimUnpacking(b,this->startTimestamp);
    doParsimUnpacking(b,this->endTimestamp);
    doParsimUnpacking(b,this->enqueueTimestamp);
    doParsimUnpacking(b,this->dequeueTimestamp);
    doParsimArrayUnpacking(b,this->energyCost,60);
    doParsimUnpacking(b,this->priority);
}

int EnergyMsg::getSource() const
{
    return this->source;
}

void EnergyMsg::setSource(int source)
{
    this->source = source;
}

int EnergyMsg::getDestination() const
{
    return this->destination;
}

void EnergyMsg::setDestination(int destination)
{
    this->destination = destination;
}

int EnergyMsg::getHopCount() const
{
    return this->hopCount;
}

void EnergyMsg::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

unsigned int EnergyMsg::getTimestampArraySize() const
{
    return 60;
}

const char * EnergyMsg::getTimestamp(unsigned int k) const
{
    if (k>=60) throw omnetpp::cRuntimeError("Array of size 60 indexed by %lu", (unsigned long)k);
    return this->timestamp[k].c_str();
}

void EnergyMsg::setTimestamp(unsigned int k, const char * timestamp)
{
    if (k>=60) throw omnetpp::cRuntimeError("Array of size 60 indexed by %lu", (unsigned long)k);
    this->timestamp[k] = timestamp;
}

::omnetpp::simtime_t EnergyMsg::getStartTimestamp() const
{
    return this->startTimestamp;
}

void EnergyMsg::setStartTimestamp(::omnetpp::simtime_t startTimestamp)
{
    this->startTimestamp = startTimestamp;
}

::omnetpp::simtime_t EnergyMsg::getEndTimestamp() const
{
    return this->endTimestamp;
}

void EnergyMsg::setEndTimestamp(::omnetpp::simtime_t endTimestamp)
{
    this->endTimestamp = endTimestamp;
}

::omnetpp::simtime_t EnergyMsg::getEnqueueTimestamp() const
{
    return this->enqueueTimestamp;
}

void EnergyMsg::setEnqueueTimestamp(::omnetpp::simtime_t enqueueTimestamp)
{
    this->enqueueTimestamp = enqueueTimestamp;
}

::omnetpp::simtime_t EnergyMsg::getDequeueTimestamp() const
{
    return this->dequeueTimestamp;
}

void EnergyMsg::setDequeueTimestamp(::omnetpp::simtime_t dequeueTimestamp)
{
    this->dequeueTimestamp = dequeueTimestamp;
}

unsigned int EnergyMsg::getEnergyCostArraySize() const
{
    return 60;
}

double EnergyMsg::getEnergyCost(unsigned int k) const
{
    if (k>=60) throw omnetpp::cRuntimeError("Array of size 60 indexed by %lu", (unsigned long)k);
    return this->energyCost[k];
}

void EnergyMsg::setEnergyCost(unsigned int k, double energyCost)
{
    if (k>=60) throw omnetpp::cRuntimeError("Array of size 60 indexed by %lu", (unsigned long)k);
    this->energyCost[k] = energyCost;
}

int EnergyMsg::getPriority() const
{
    return this->priority;
}

void EnergyMsg::setPriority(int priority)
{
    this->priority = priority;
}

class EnergyMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EnergyMsgDescriptor();
    virtual ~EnergyMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EnergyMsgDescriptor)

EnergyMsgDescriptor::EnergyMsgDescriptor() : omnetpp::cClassDescriptor("EnergyMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

EnergyMsgDescriptor::~EnergyMsgDescriptor()
{
    delete[] propertynames;
}

bool EnergyMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EnergyMsg *>(obj)!=nullptr;
}

const char **EnergyMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EnergyMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EnergyMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount() : 10;
}

unsigned int EnergyMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *EnergyMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "hopCount",
        "timestamp",
        "startTimestamp",
        "endTimestamp",
        "enqueueTimestamp",
        "dequeueTimestamp",
        "energyCost",
        "priority",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int EnergyMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTimestamp")==0) return base+4;
    if (fieldName[0]=='e' && strcmp(fieldName, "endTimestamp")==0) return base+5;
    if (fieldName[0]=='e' && strcmp(fieldName, "enqueueTimestamp")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "dequeueTimestamp")==0) return base+7;
    if (fieldName[0]=='e' && strcmp(fieldName, "energyCost")==0) return base+8;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+9;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EnergyMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "string",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "double",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
}

const char **EnergyMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EnergyMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EnergyMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EnergyMsg *pp = (EnergyMsg *)object; (void)pp;
    switch (field) {
        case 3: return 60;
        case 8: return 60;
        default: return 0;
    }
}

const char *EnergyMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EnergyMsg *pp = (EnergyMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EnergyMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EnergyMsg *pp = (EnergyMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSource());
        case 1: return long2string(pp->getDestination());
        case 2: return long2string(pp->getHopCount());
        case 3: return oppstring2string(pp->getTimestamp(i));
        case 4: return simtime2string(pp->getStartTimestamp());
        case 5: return simtime2string(pp->getEndTimestamp());
        case 6: return simtime2string(pp->getEnqueueTimestamp());
        case 7: return simtime2string(pp->getDequeueTimestamp());
        case 8: return double2string(pp->getEnergyCost(i));
        case 9: return long2string(pp->getPriority());
        default: return "";
    }
}

bool EnergyMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EnergyMsg *pp = (EnergyMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2long(value)); return true;
        case 1: pp->setDestination(string2long(value)); return true;
        case 2: pp->setHopCount(string2long(value)); return true;
        case 3: pp->setTimestamp(i,(value)); return true;
        case 4: pp->setStartTimestamp(string2simtime(value)); return true;
        case 5: pp->setEndTimestamp(string2simtime(value)); return true;
        case 6: pp->setEnqueueTimestamp(string2simtime(value)); return true;
        case 7: pp->setDequeueTimestamp(string2simtime(value)); return true;
        case 8: pp->setEnergyCost(i,string2double(value)); return true;
        case 9: pp->setPriority(string2long(value)); return true;
        default: return false;
    }
}

const char *EnergyMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EnergyMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EnergyMsg *pp = (EnergyMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


