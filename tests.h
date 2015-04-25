#include <vector>
#include <ctime>
#include <algorithm>
#include "deque.h"



struct Query
{
    EQueryType type;
    int key;
    ui32 index;
};


std::string convertQueryToString(Query query)
{
    switch (query.type)
    {
        case PUSH_BACK:
            return "PUSH_BACK " + convertToString(query.key);
        case PUSH_FRONT:
            return "PUSH_FRONT " + convertToString(query.key);
        case POP_BACK:
            return "POP_BACK";
        case POP_FRONT:
            return "POP_FRONT";
        case GET_ELEMENT:
            return "GET_ELEMENT " + convertToString(query.index);
        default:
            return "What the hell?!";
    }
}

std::vector<Query> generateQueries(ui32 queriesNumber)
{
    std::vector<Query> queries;
    ui32 size = 0;
    for (ui32 i = 0; i < queriesNumber; ++i)
    {
        Query currentQuery;
        if (size)
            currentQuery.type = (EQueryType)getRandomInt(0, (int)OPERATIONS_NUMBER - 1);
        else
            currentQuery.type = (EQueryType)getRandomInt(0, (int)POP_BACK - 1);
        switch (currentQuery.type)
        {
            case PUSH_BACK:
            {
                currentQuery.key = getRandomInt();
                ++size;
                break;
            }
            case PUSH_FRONT:
            {
                currentQuery.key = getRandomInt();
                ++size;
                break;
            }
            case POP_BACK:
            {
                --size;
                break;
            }
            case POP_FRONT:
            {
                --size;
                break;
            }
            case GET_ELEMENT:
            {
                currentQuery.index = getRandomInt(0, size - 1);
                break;
            }
        }
        queries.push_back(currentQuery);
    }
    return queries;
}

void resultQuery(Deque<int> &deque, Query query)
{
    switch(query.type)
    {
        case PUSH_BACK:
        {
            deque.push_back(query.key);
            break;
        }
        case PUSH_FRONT:
        {
            deque.push_front(query.key);
            break;
        }
        case POP_BACK:
        {
            deque.pop_back();
            break;
        }
        case POP_FRONT:
        {
            deque.pop_front();
            break;
        }
        case GET_ELEMENT:
        {
            deque[query.index];
            break;
        }
    }
}

void resultQueries(Deque<int> &deque, std::vector<Query> &queries)
{
    for (ui32 i = 0; i < queries.size(); ++i)
    {
        resultQuery(deque, queries[i]);
    }
}

class GlobalTestResult
{
    void test(ui32 queriesNumber)
    {

        std::vector<Query> queries = generateQueries(queriesNumber);
        Deque<int> deque;
        clock_t beginTime, endTime;
        beginTime = clock();
        resultQueries(deque, queries);
        endTime = clock();
        time = (double)(endTime - beginTime)/CLOCKS_PER_SEC;
    }

public:
    double time;

    GlobalTestResult(){};

    void execute(ui32 queriesNumber)
    {
        test(queriesNumber);
    }
};
