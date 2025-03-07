/**
 * @file TopologicalSortVisitor.cpp
 * @author Attulya Pratap Gupta
 */

#include "pch.h"
#include "TopologicalSortVisitor.h"
#include "PinVisitor.h"
#include "Pin.h"
#include "Gate.h"
#include "GateDFlipFlop.h"
#include "GateNot.h"
#include "GateAnd.h"
#include "GateOr.h"
#include "GateSRFlipFlop.h"

/**
 * Helper function to sort pins in each gate
 * @param gate whose pins we're sorting
 * */
void TopologicalSortVisitor::VisitGateHelper(Gate* gate) {
    // Check for cyclic dependencies
    if (mTemporaryMark.find(gate) != mTemporaryMark.end()) {
        return; // Skip if already in temporary mark (handles cycles)
    }

    // Skip if already visited
    if (mVisited.find(gate) != mVisited.end()) {
        return;
    }

    // Add temporary mark
    mTemporaryMark.insert(gate);

    // Visit connected gates through output pins
    auto outputPins = gate->GetOutputPins();

    PinVisitor pinVisitor;
    if (outputPins.first) {
        outputPins.first->Accept(&pinVisitor);
        for (auto pin : pinVisitor.GetCollectedPins()) {
            if (pin->GetOwner()) {
                pin->GetOwner()->Accept(this);
            }
        }
    }

    if (outputPins.second) {
        pinVisitor = PinVisitor();
        outputPins.second->Accept(&pinVisitor);
        for (auto pin : pinVisitor.GetCollectedPins()) {
            if (pin->GetOwner()) {
                pin->GetOwner()->Accept(this);
            }
        }
    }

    // Remove temporary mark
    mTemporaryMark.erase(gate);

    // Add to visited set
    mVisited.insert(gate);

    // Push to stack instead of directly to sorted list
    mGateStack.push(gate);
}

/**
 *  Function to finalize sorting and get sorted list of gates
 * */
void TopologicalSortVisitor::FinalizeSorting() {
    // Clear any existing sorted gates
    mSortedGates.clear();

    // Pop from stack and add to sorted list
    while (!mGateStack.empty()) {
        Gate* gate = mGateStack.top();
        mGateStack.pop();
        mSortedGates.push_back(gate->shared_from_this());
    }
}

/**
 * Function to visit AND Gate
 * @param gate to visit
 * */
void TopologicalSortVisitor::VisitGateAnd(GateAnd* gate)
{
    VisitGateHelper(gate);
}

/**
 * Function to visit OR Gate
 * @param gate to visit
 * */
void TopologicalSortVisitor::VisitGateOr(GateOr* gate)
{
    VisitGateHelper(gate);
}

/**
 * Function to visit NOT Gate
 * @param gate to visit
 * */
void TopologicalSortVisitor::VisitGateNot(GateNot* gate)
{
    VisitGateHelper(gate);
}

/**
 * Function to visit DFlipFlop Gate
 * @param gate to visit
 * */
void TopologicalSortVisitor::VisitGateDFlipFlop(GateDFlipFlop* gate)
{
    VisitGateHelper(gate);
}

/**
 * Function to visit SRFlipFlop Gate
 * @param gate to visit
 * */
void TopologicalSortVisitor::VisitGateSRFlipFlop(GateSRFlipFlop* gate)
{
    VisitGateHelper(gate);
}