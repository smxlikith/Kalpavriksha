#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; i++) {
        int req = target - nums[i];
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] == req) {
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }
    return result;
}
