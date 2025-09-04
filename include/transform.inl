#pragma once

#include <queue>

template <typename T>
std::vector<T*> Transform::findTypeInChildren()
{
    std::queue<Transform*> toCheck = std::queue<Transform*>();
    std::vector<T*> found = std::vector<T*>();

    toCheck.push(this);
    while (!toCheck.empty())
    {
        T* target = dynamic_cast<T*>(toCheck.front());
        if (target != nullptr)
            found.push_back(target);

        for (size_t i = 0; i < toCheck.front()->countChildren(); i++)
        {
            toCheck.push(toCheck.front()->getChild(i));
        }

        toCheck.pop();
    }

    return found;
}