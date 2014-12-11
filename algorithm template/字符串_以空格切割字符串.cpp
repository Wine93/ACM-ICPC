//以标记符ch切割字符串, 返回其中整数
vector<int> Cut(char s[], char *ch)
{
    int val;
    vector<int> ans;
    char *p = strtok(s, ch);
    while (p)
    {
        sscanf (p, "%d", &val);
        ans.push_back(val);
        p = strtok(NULL, ch);
    }
    return ans;
}