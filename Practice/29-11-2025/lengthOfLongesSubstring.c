int lengthOfLongestSubstring(char* s) {
    int maxSize = 0;
    char freq[256] = {0};
    for (int l = 0, r = 0; r < strlen(s); r++) {
        freq[s[r]]++;
        while (l < r && freq[s[r]] > 1) {
            freq[s[l++]]--;
        }
        maxSize = (r - l + 1) > maxSize ? (r - l + 1) : maxSize;
    }
    return maxSize;
}