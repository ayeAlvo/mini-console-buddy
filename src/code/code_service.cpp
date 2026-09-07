#include "code/code_service.h"

static CodeItem items[] = {
    {
        "> git status",
        "Shows the current state\nof your repository."
    },
    {
        "> git log --oneline",
        "Shows a compact list\nof recent commits."
    },
    {
        "> git branch",
        "Lists your local\nGit branches."
    },
    {
        "> docker ps",
        "Shows running\nDocker containers."
    },
    {
        "> pwd",
        "Shows the current\nworking directory."
    }
};

static int currentIndex = 0;

const CodeItem &codeGetCurrentItem()
{
    return items[currentIndex];
}

const CodeItem &codeGetNextItem()
{
    currentIndex++;

    if (currentIndex >= 5)
    {
        currentIndex = 0;
    }

    return items[currentIndex];
}