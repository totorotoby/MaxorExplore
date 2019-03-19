import copy
import random

# Class for the nodes of the decision tree
class Node:

    def __init__(self, isLeaf, seen, unseen, ty, children=None, reward = None):

        self.isLeaf = isLeaf
        self.reward = reward
        self.seen = seen
        self.unseen = unseen
        self.explore = None
        self.maximize = None
        self.type = ty


    def __str__(self):
        return "type:  " + self.type + " seen states: "  + str(self.seen) + " unseen states: " + str(self.unseen) + " last reward: " + str(self.reward)

    
    def addChildren(self, ex=None, maxim=None):
        self.explore = ex
        self.maximize = maxim

    def addReward(self, reward):
        self.reward = reward



# constructs tree from the value set, and time length
def buildTree(node, T, t, V):

    if t < T:
        t += 1
        
        if t == T - 1:
            isleaf = True
        else:
            isleaf = False
        
        if t < len(V):

            # exploration child
            new_unseen = copy.deepcopy(node.unseen)
            new_unseen.remove(V[t])

            explore = Node(isleaf, seen=node.seen + [V[t]],
                    unseen = new_unseen,
                    ty='E', reward=V[t])
    
            # maximize child
            maximize = Node(isleaf, seen=node.seen, unseen=node.unseen, ty='M',
                    reward=max(node.seen))

            node.addChildren(explore,maximize)

            buildTree(node.explore, T, t, V)
            buildTree(node.maximize, T, t, V)

        else:
            maximize = Node(isleaf, seen=node.seen, unseen=node.unseen, ty='M',
                    reward=max(node.seen))
            node.addChildren(maxim=maximize)
            
            buildTree(node.maximize, T, t, V)
            #print(node, len(V), t)

# gets the total rewards from top to bottom leafs in list L
def extoMaxRewards(root, R, L):

    if root.isLeaf == False:

        R+=root.reward
        extoMaxRewards(root.maximize, R, L)
        if root.explore != None:
            extoMaxRewards(root.explore, R, L)

    if root.isLeaf == True:
        L.append(R)

    
# simple print repersentation of the tree
def printTree(root, count):
    
    print(count * "\t", root)
    if not root.isLeaf:
        if root.explore != None:
            printTree(root.explore, count + 1)
        printTree(root.maximize, count + 1)


def main():
 
    T = 5
    t = 0
    V = [5, 2, 9, 7, 3, 7, 7, 8, 2, 8, 9, 10, 3]
    seen = [V[0]]
    unseen = V[t+1:len(V)]
    tree = Node(False, seen, unseen, ty='E', reward = V[0])
    buildTree(tree, T, t, V)
    #printTree(tree, 0) 

    rewardList = []
    extoMaxRewards(tree, 0, rewardList)
    print(rewardList, len(rewardList))
    



main()
