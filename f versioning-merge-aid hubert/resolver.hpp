//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
#define MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP

#include "parsedCode.hpp"
#include "parser.hpp"
#include "fileHandler.hpp"
#include "printHandler.hpp"

class resolver
{
private:
    parsedCode instance;
    printHandler printer;
    coloredStringVector printingData;
    int currentConflictIndex;
    int currentPrintingPosition;
    std::vector<std::pair<int,int>> foundPositions;
    int currentFoundIndex;

public:
    explicit resolver() : instance(stringVector(), conflictsVector()), currentConflictIndex(-1), foundPositions(), currentPrintingPosition(0)
    {}

    void load(const std::string& filename)
    {
        auto lines = readLinesFromFile(filename);
        instance = parseConflicts(lines);
        printer.setup(instance.getTotalLength());
//        selectCurrentConflict();
        refreshPrintingData();
//        getPrintingIndex();
    }

    void save(const std::string& filename)
    {
        auto newLines = instance.getLines();
        writeLinesToFile(newLines, filename);
    }

    void find(const std::string & pattern)
    {
        foundPositions = instance.findPattern(pattern);
        currentFoundIndex = 0;
        setPrintingPositionFromFound();
        refreshPrintingData();
    }

    void nextFound()
    {
        currentFoundIndex++;

        if (currentFoundIndex >= foundPositions.size())
            currentFoundIndex = 0;

        setPrintingPositionFromFound();
        refreshPrintingData();
    }

    void previousFound()
    {
        currentFoundIndex--;

        if (currentFoundIndex < 0)
            currentFoundIndex = foundPositions.size() - 1;

        setPrintingPositionFromFound();
        refreshPrintingData();
    }

    void printToTerminal()
    {
        printer.printOnScreen(printingData, currentPrintingPosition);
    }

    void nextLine()
    {
        if (currentPrintingPosition < printingData.size() - 1)
            currentPrintingPosition++;
    }

    void previousLine()
    {
        currentPrintingPosition--;
        if (currentPrintingPosition < 0)
            currentPrintingPosition = 0;
    }

    void nextConflict()
    {
        if (instance.conflictsSize() > 0) {
            currentConflictIndex++;

            if (currentConflictIndex >= instance.conflictsSize())
                currentConflictIndex = 0;

            selectCurrentConflict();
            getPrintingIndex();
            refreshPrintingData();
        }
    }

    void previousConflict()
    {
        if (instance.conflictsSize() > 0) {
            currentConflictIndex--;

            if (currentConflictIndex < 0)
                currentConflictIndex = instance.conflictsSize() - 1;

            selectCurrentConflict();
            getPrintingIndex();
            refreshPrintingData();
        }
    }

    void jumpToConflict(int index)
    {
        if (index <= instance.conflictsSize())
            currentConflictIndex = index;

        selectCurrentConflict();
        getPrintingIndex();
        refreshPrintingData();
    }

    void revertCurrent()
    {
        if (currentConflictIndex == -1)
            return;
        instance.revertConflict(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToOld()
    {
        if (currentConflictIndex == -1)
            return;
        instance.mergeToOld(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToNew()
    {
        if (currentConflictIndex == -1)
            return;
        instance.mergeToNew(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToBoth()
    {
        if (currentConflictIndex == -1)
            return;
        instance.mergeToBoth(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToBothR()
    {
        if (currentConflictIndex == -1)
            return;
        instance.mergeToBothR(currentConflictIndex);
        refreshPrintingData();
    }

private:

    void getPrintingIndex()
    {
        currentPrintingPosition = instance.getConflictPosition(currentConflictIndex);
    }
    void refreshPrintingData()
    {
        printingData = instance.getLinesColored();
    }

    void setPrintingPositionFromFound()
    {
        if (!foundPositions.empty()) {
            currentPrintingPosition = foundPositions[currentFoundIndex].second;
            currentConflictIndex = foundPositions[currentFoundIndex].first;
            selectCurrentConflict();
        }
    }

    void selectCurrentConflict() { instance.selectConflict(currentConflictIndex); }
};

#endif //MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
