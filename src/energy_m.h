//
// Generated file, do not edit! Created by nedtool 5.2 from src/energy.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __ENERGY_M_H
#define __ENERGY_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0502
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>src/energy.msg:3</tt> by nedtool.
 * <pre>
 * message EnergyMsg
 * {
 *     int source;
 *     int destination;
 *     int hopCount = 0;
 *     long timestamp[60];
 *     double energyCost[60];
 *     int priority;
 * }
 * </pre>
 */
class EnergyMsg : public ::omnetpp::cMessage
{
  protected:
    int source;
    int destination;
    int hopCount;
    long timestamp[60];
    double energyCost[60];
    int priority;

  private:
    void copy(const EnergyMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EnergyMsg&);

  public:
    EnergyMsg(const char *name=nullptr, short kind=0);
    EnergyMsg(const EnergyMsg& other);
    virtual ~EnergyMsg();
    EnergyMsg& operator=(const EnergyMsg& other);
    virtual EnergyMsg *dup() const override {return new EnergyMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getDestination() const;
    virtual void setDestination(int destination);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual unsigned int getTimestampArraySize() const;
    virtual long getTimestamp(unsigned int k) const;
    virtual void setTimestamp(unsigned int k, long timestamp);
    virtual unsigned int getEnergyCostArraySize() const;
    virtual double getEnergyCost(unsigned int k) const;
    virtual void setEnergyCost(unsigned int k, double energyCost);
    virtual int getPriority() const;
    virtual void setPriority(int priority);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EnergyMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EnergyMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __ENERGY_M_H

