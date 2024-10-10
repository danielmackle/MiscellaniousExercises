from statistics import mode
class Solution(object):
    def minCostToMoveChips(position):
        """
        :type position: List[int]
        :rtype: int
        """
        if(len(position)==0):
            return 0
        #find largest value of position
        position.sort
        mostCommon = mode(position)
        print(mostCommon)
        #count each movement
        cost=0
        for p in position:
            if p != mostCommon:
                cost = cost+1
        return cost
    
    position = [1,3,6,8,1,1,2,2,2,2,3,4]
    print(minCostToMoveChips(position))