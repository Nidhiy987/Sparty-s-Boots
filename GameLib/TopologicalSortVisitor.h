/**
 * @file TopologicalSortVisitor.h
 * @author Attulya Pratap Gupta
 *
 */


#ifndef TOPOLOGICALSORTVISITOR_H
#define TOPOLOGICALSORTVISITOR_H

#include "VisitorBase.h"
#include <vector>
#include <set>
#include <memory>
#include <stack>

/**
 *  Class used to topologically sort pins in the game
 * */
class TopologicalSortVisitor : public VisitorBase {
private:
    /// List of sorted gates
    std::vector<std::shared_ptr<Gate>> mSortedGates;

    /// Set of visited gates
    std::set<Gate*> mVisited;

    /// Set of temporarily marked gates
    std::set<Gate*> mTemporaryMark;

    /// Stack of gates
    std::stack<Gate*> mGateStack;  // Added stack for post-order traversal

    void VisitGateHelper(Gate* gate);

public:
    void VisitGateAnd(GateAnd* gate) override;
    void VisitGateOr(GateOr* gate) override;
    void VisitGateNot(GateNot* gate) override;
    void VisitGateDFlipFlop(GateDFlipFlop* gate) override;
    void VisitGateSRFlipFlop(GateSRFlipFlop* gate) override;

    /**
     * Getter for sorted gates
     * @return sorted gates
     * */
    const std::vector<std::shared_ptr<Gate>>& GetSortedGates() const { return mSortedGates; }
    void FinalizeSorting();  // New method to convert stack to final order
};

#endif