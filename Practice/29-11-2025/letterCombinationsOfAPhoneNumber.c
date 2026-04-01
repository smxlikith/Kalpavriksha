char* map[] = {"", "", "abc", "def", "ghi",
               "jkl", "mno", "pqrs", "tuv", "wxyz"};

int retSize(char* digits) {
    int res = 1;
    for (int i = 0; i < strlen(digits); i++) {
        res *= strlen(map[digits[i] - '0']);
    }
    return res;
}

void helper(int currIdx, char curr[], int digIdx, char* digits, int* resIdx, char** result) {
    if (currIdx == strlen(digits)) {
        result[(*resIdx)] = malloc(strlen(digits) + 1);
        strcpy(result[(*resIdx)], curr);
        *resIdx += 1;
        return;
    }
    char* s = map[digits[digIdx] - '0'];
    for (int i = 0; i < strlen(s); i++) {
        curr[currIdx] = s[i];
        helper(currIdx + 1, curr, digIdx + 1, digits, resIdx, result);
    }
}

char** letterCombinations(char* digits, int* returnSize) {
    *returnSize = retSize(digits);
    char** result = malloc(*returnSize * sizeof(char*));

    int resIdx = 0;
    char curr[9] = "";

    helper(0, curr, 0, digits, &resIdx, result);

    return result;
}