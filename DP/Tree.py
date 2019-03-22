import copy
import random
import math

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


    def display(self):
        lines, _, _, _ = self._display_aux()
        for line in lines:
            print(line)

    def _display_aux(self):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child.
        if self.maximize is None and self.explore is None:
            line = '%s' % self.reward
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child.
        if self.maximize is None:
            lines, n, p, x = self.explore._display_aux()
            s = '%s' % self.reward
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child.
        if self.explore is None:
            lines, n, p, x = self.maximize._display_aux()
            s = '%s' % self.reward
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children.
        left, n, p, x = self.explore._display_aux()
        right, m, q, y = self.maximize._display_aux()
        s = '%s' % self.reward
        u = len(s)
        first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s + y * '_' + (m - y) * ' '
        second_line = x * ' ' + '/' + (n - x - 1 + u + y) * ' ' + '\\' + (m - y - 1) * ' '
        if p < q:
            left += [n * ' '] * (q - p)
        elif q < p:
            right += [m * ' '] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * ' ' + b for a, b in zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2



# constructs tree from the value set, and time length
def buildTree(node, T, t, V, maxNum):

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

            explore = Node(isleaf, seen=node.seen + [V[t-maxNum]],
                    unseen = new_unseen,
                    ty='E', reward=V[t-maxNum])
            print(t, V[t])
            # maximize child
            maximize = Node(isleaf, seen=node.seen, unseen=node.unseen, ty='M',
                    reward=max(node.seen))

            node.addChildren(explore,maximize)

            buildTree(node.explore, T, t, V, maxNum)
            buildTree(node.maximize, T, t, V, maxNum+1)

        else:
            maximize = Node(isleaf, seen=node.seen, unseen=node.unseen, ty='M',
                    reward=max(node.seen))
            node.addChildren(maxim=maximize)
            
            buildTree(node.maximize, T, t, V, maxNum+1)
            print(node, t)

# gets the total rewards from top to bottom leafs in list L
def extoMaxRewards(root, R, L):

    if root.isLeaf == False:

        R+=root.reward
        

        if root.explore != None:
            extoMaxRewards(root.explore, R, L)
        
        extoMaxRewards(root.maximize, R, L)

    if root.isLeaf == True:
        R+=root.reward
        L.append(R)


def getRelRewards(L, T):

    f_indices = []

    for i in range(1,T):
        f_indices.append(int(math.pow(2,T-(i+1))-1))
    f_indices.reverse()

    s_indices = []
    for i in range(1,T):
      s_indices.append(int(math.pow(2,T-1) - math.pow(2, T - (i+1))))  

    indices = f_indices + s_indices

    return [ L[index] for index in indices]

    
# simple print repersentation of the tree
def printTree(root, count):
    
    print(count * "\t", root)
    if not root.isLeaf:
        if root.explore != None:
            printTree(root.explore, count + 1)
        printTree(root.maximize, count + 1)


def main():
 
    T = 4
    t = 0
    V = [5, 2, 9, 7, 3]
    seen = [V[0]]
    unseen = V[t+1:len(V)]
    tree = Node(False, seen, unseen, ty='E', reward = V[0])
    buildTree(tree, T, t, V, 0)

    tree.display()
    #printTree(tree, 0) 

    rewardList = []
    extoMaxRewards(tree, 0, rewardList)
    rewards = getRelRewards(rewardList, T)
    #print(rewardList)





main()
