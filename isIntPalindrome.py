class Solution(object):
    def isPalindrome(x):
        """
        :type x: int
        :rtype: bool
        """
        try:
            val = int(x)
        except ValueError:
            return False
        arrInt = [str(x) for x in str(x)]
        arrInt.sort
        sortedStr = ' '
        sortedStr.join(arrInt)
        if(int(sortedStr) == x):
            return True
        return False
    isPalindrome(1221)