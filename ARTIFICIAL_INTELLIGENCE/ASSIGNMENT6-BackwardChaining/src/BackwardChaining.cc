/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining BC class file
 */

#include "utils.h"

std::vector<std::string> BackwardChaining::buildFactsList(const std::string &current, const std::string &type) const {
  std::vector<std::string> list;
  for (const auto &f : initialFactsOrdered) {
    list.push_back(f);
  }
  if (type == "initial") {
    return list;
  } else if (type == "earlier") {
    if (find(list.begin(), list.end(), current) == list.end()) {
      list.push_back(current);
    }
    return list;
  } else {
    for (const auto &f : inferredOrder) {
      if (find(list.begin(), list.end(), f) == list.end()) {
        list.push_back(f);
      }
      if (f == current) {
        break;
      }
    }
    if (find(list.begin(), list.end(), current) == list.end()){
      list.push_back(current);
    }
    return list;
  }
}

bool BackwardChaining::proveGoal(const std::string &currentGoal, int depth, std::set<std::string> &inProgress, std::vector<std::string> &outPath) {
  std::string indent = getIndent(depth);
  if (inProgress.count(currentGoal)) {
    std::stringstream ss;
    ss << stepTag(traceCounter++) << ") " << indent << "Goal " << currentGoal << ". Cycle. Backtrack, FAIL.\n";
    trace.push_back(ss.str());
    return false;
  }
  if (initialFacts.count(currentGoal)) {
    std::string factsStr = joinFactsList(buildFactsList(currentGoal, "initial"));
    std::stringstream ss;
    ss << stepTag(traceCounter++) << ") " << indent << "Goal " << currentGoal
      << ". Fact (initial), as facts " << factsStr << ". Backtrack, OK.\n";
    trace.push_back(ss.str());
    outPath.clear();
    return true;
  }
  if (memoTrue.count(currentGoal)) {
    std::string factsStr = joinFactsList(buildFactsList(currentGoal, "earlier"));
    std::stringstream ss;
    ss << stepTag(traceCounter++) << ") " << indent << "Goal " << currentGoal
      << ". Fact (earlier inferred), as facts " << factsStr << ". Backtrack, OK.\n";
    trace.push_back(ss.str());
    outPath = memoProofTrue.at(currentGoal);
    return true;
  }
  std::vector<Rule> applicable;
  for (const auto &r : rules) {
    if (r.rhs == currentGoal) {
      applicable.push_back(r);
    }
  }
  if (applicable.empty()) {
    std::stringstream ss;
    ss << stepTag(traceCounter++) << ") " << indent
      << "Goal " << currentGoal << ". No rules. Backtrack, FAIL.\n";
    trace.push_back(ss.str());
    return false;
  }
  inProgress.insert(currentGoal);
  bool anyTried = false;
  for (const auto &rule : applicable) {
    anyTried = true;
    {
      std::stringstream ss;
      ss << stepTag(traceCounter++) << ") " << indent << "Goal " << currentGoal << " .Find" << rule.toString() << ". New goals ";
      for (size_t i = 0; i < rule.lhs.size(); i++) {
        ss << rule.lhs[i];
        if (i < rule.lhs.size() - 1) {
          ss << ", ";
        }
      }
      ss << ".\n";
      trace.push_back(ss.str());
    }
    bool allProved = true;
    std::vector<std::string> accPath;
    for (const auto &sub : rule.lhs) {
      std::vector<std::string> subPath;
      if (!proveGoal(sub,depth + 1, inProgress, subPath)) {
        allProved = false;
        break;
      }
      accPath.insert(accPath.end(), subPath.begin(), subPath.end());
    }
    if (allProved) {
      accPath.push_back(rule.name);
      memoTrue.insert(currentGoal);
      memoProofTrue[currentGoal] = accPath;
      inferredOrder.push_back(currentGoal);
      {
        std::string factsStr = joinFactsList(buildFactsList(currentGoal, "present"));
        std::stringstream ss;
        ss << stepTag(traceCounter++) << ") " << indent
          << "Goal " << currentGoal << ". Fact (presently inferred). Facts "
          << factsStr;
        if (depth == 0) {
          ss << ". OK.\n";
        } else {
          ss << ". Backtrack, OK.\n";
        }
        trace.push_back(ss.str());
      }
      outPath = accPath;
      inProgress.erase(currentGoal);
      return true;
    }
  }
  inProgress.erase(currentGoal);
  if (anyTried) {
    std::stringstream ss;
    ss << stepTag(traceCounter++) << ") " << indent << "Goal " << currentGoal << ". No more rules. Backtrack, FAIL.\n";
    trace.push_back(ss.str());
  }
  return false;
}
