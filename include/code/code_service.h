#pragma once

struct CodeItem {
    const char* command;
    const char* description;
};

const CodeItem &codeGetCurrentItem();
const CodeItem &codeGetNextItem();