#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <array>
#include <unordered_map>
#include <string>

using namespace std;


#define _2D vector <vector <int> >

const int inf = 10000000;

struct Node
{
    _2D board;
    int g;
    int h; //heuristic
    int f; // f = g + h => f = move_count + h
    int zero_index [2];
    string move;
    Node* link;
    int limit;
    int prev_zero_index[2];
    
};
struct NodeCompare
{
	bool operator()(const Node &n1, const Node &n2) const
	{
		return n1.f > n2.f;
	}
};

void display_board(_2D goal)
{
    for (int i = 0; i < goal.size(); i++)
    {
        for (int j = 0; j < goal.size(); j++)
        {
            cout << " " << goal.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void display_board(Node curr)
{
    for (int i = 0; i < curr.board.size(); i++)
    {
        for (int j = 0; j < curr.board.size(); j++)
        {
            cout << " " << curr.board.at(i).at(j) << " ";
        }
        cout << endl;        
    }
    cout << endl;
}
//incremental get_h overload
int get_h (Node newNode, Node curr, _2D &goal)
{
    int curr_value = 0;
    int new_value = 0;
    for(int i = 0; i < newNode.board.size(); i++)
    {
        for(int j = 0; j < newNode.board.size(); j++)
        {
            if(goal.at(i).at(j) == newNode.board.at(curr.zero_index[0]).at(curr.zero_index[1]))
            {
                new_value = abs(curr.zero_index[0] - i) + abs(curr.zero_index[1] - j);
            }
            if(goal.at(i).at(j) == curr.board.at(newNode.zero_index[0]).at(newNode.zero_index[1]))
            {
                curr_value = abs(newNode.zero_index[0] - i) + abs(newNode.zero_index[1] - j);
            }
        }
    }
    return curr.h + (new_value - curr_value);
}

int get_h(Node current, _2D &goal)
{
    
    int sum = 0;
    for (int i = 0; i < goal.size(); i++)
    {
        for (int j = 0; j < goal.size(); j++)
        {
            if (current.board.at(i).at(j) == 0)
            {
                continue;
            }
            for (int k = 0; k < goal.size(); k++)
            {
                for (int l = 0; l < goal.size(); l++)
                {
                    if (current.board.at(i).at(j) == goal.at(k).at(l) && goal.at(k).at(l) != -1)
                    {
                        sum += abs(k - i) + abs(l - j);
                        
                        
                    }
                    
                }
            }
            
        }
    }

    return sum;
}

int get_h(Node * & curr)
{
    int count = 0;
    int sum = 0;
    for (int i = 0; i < curr -> board.size(); i++)
    {
        for (int j = 0; j < curr -> board.size(); j++)
        {
            if (curr -> board.at(i).at(j) != count && curr -> board.at(i).at(j) != 0)
            {
                sum += 1;
            }
            count += 1;
        }
    }
    return sum;
}

inline Node * create_expand_node(Node * &curr, string move, _2D &new_board, _2D &goal)
{
    Node * newNode = new Node;
    if (move == "DOWN")
    {
        newNode -> zero_index[0] = curr -> zero_index[0] + 1;
        newNode -> zero_index[1] = curr -> zero_index[1];
    }
    else if (move == "UP")
    {
        newNode -> zero_index[0] = curr -> zero_index[0] - 1;
        newNode -> zero_index[1] = curr -> zero_index[1];
    }
    else if (move == "RIGHT")
    {
        newNode -> zero_index[0] = curr -> zero_index[0];
        newNode -> zero_index[1] = curr -> zero_index[1] + 1;
    }
    else if (move == "LEFT")
    {
        newNode -> zero_index[0] = curr -> zero_index[0];
        newNode -> zero_index[1] = curr -> zero_index[1] - 1;
    }
    
    newNode -> board = new_board;
    newNode -> g = curr -> g + 1;
    newNode -> h = get_h(*newNode, *curr, goal);
    newNode -> f = newNode -> h + newNode -> g;
    newNode -> link = curr;
    newNode -> move = move;
    newNode -> limit = curr -> limit;
    newNode -> prev_zero_index[0] = curr -> zero_index[0];
    newNode -> prev_zero_index[1] = curr -> zero_index[1];
    return newNode;
}


Node * expand(Node* &curr, _2D &goal)
{
    int temp = 0;
    Node *min = new Node;
    min -> f = 100;
    if (curr -> f > curr -> limit )
    {
        return curr;
    }
    else if (curr -> h == 0)
    {

        cout << "goal reached" << endl;
        return curr;
    }
    else
    {
        if (curr -> zero_index[0] <= curr -> board.size() - 2 && curr -> zero_index[0] + 1 != curr -> prev_zero_index[0])
        {
            _2D new_board = curr -> board;
            swap(new_board[curr -> zero_index[0]][curr -> zero_index[1]], new_board[curr -> zero_index[0] + 1][curr -> zero_index[1]]);
            Node * newNode = create_expand_node(curr, "DOWN", new_board, goal);
            Node * solution = expand(newNode, goal);
            if (solution -> h == 0)
            {
                return solution;
            }
            
            else
            {
                if (solution -> f < min -> f)
                {
                    min = solution;
                }
            }
            
    
        }
        if (curr -> zero_index[0] >= 1 && curr -> zero_index[0] - 1 != curr -> prev_zero_index[0])
        {
            _2D new_board = curr -> board;
            swap(new_board[curr -> zero_index[0]][curr -> zero_index[1]], new_board[curr -> zero_index[0] - 1][curr -> zero_index[1]]);
            Node * newNode = create_expand_node(curr, "UP", new_board, goal);
            Node * solution = expand(newNode, goal);
            if (solution -> h == 0)
            {
                return solution;
            }
            
            else
            {
                if (solution -> f < min -> f)
                {
                    min = solution;
                }
            }
            
            
        }
        if (curr -> zero_index[1] <= curr -> board.size() - 2 && curr -> zero_index[1] + 1 != curr -> prev_zero_index[1])
        {
            _2D new_board = curr -> board;
            swap(new_board[curr -> zero_index[0]][curr -> zero_index[1]], new_board[curr -> zero_index[0]][curr -> zero_index[1] + 1]);
            Node * newNode = create_expand_node(curr, "RIGHT", new_board, goal);
            Node * solution = expand(newNode, goal);
            if (solution -> h == 0)
            {
                return solution;
            }
            
            else
            {
                if (solution -> f < min -> f)
                {
                    min = solution;
                }
            }
            
        }
        if (curr -> zero_index[1] >= 1 && curr -> zero_index[1] - 1 != curr -> prev_zero_index[1])
        {
            _2D new_board = curr -> board;
            swap(new_board[curr -> zero_index[0]][curr -> zero_index[1]], new_board[curr -> zero_index[0]][curr -> zero_index[1] - 1]);
            Node * newNode = create_expand_node(curr, "LEFT", new_board, goal);
            Node * solution = expand(newNode, goal);
            if (solution -> h == 0)
            {
                return solution;
            }
            
            else
            {
                if (solution -> f < min -> f)
                {
                    min = solution;
                }
            }
            
            
        }
    }
    min -> limit = min -> f;
    return min;
}


Node * ida(_2D &board, _2D &goal, Node* &init)
{
    

    Node * solution = nullptr;
    Node  * root = init;
    root -> limit = init -> f;
    root -> prev_zero_index[0] = -1;
    root -> prev_zero_index[1] = -1;
    
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if(board[i][j] == 0)
            {
                root -> zero_index[0] = i;
                root -> zero_index[1] = j;
            }
        }
    }
    
    int count = 0;
    while (count < 10000)
    {
        solution = expand(root, goal);
        
        if (solution -> limit == 100)
        {
            return nullptr;
        }
        count += 1;
        if (count > 100000)
        {
            cout << "count exceeded" << endl;
        }
        if (solution -> h == 0)
        {
            return solution;
        }
        
        root -> limit = solution -> limit;
        //cout << solution -> f << endl;
        
    }
    return solution;
}

int main()
{
    int N = 0;
    
    cin >> N;
    vector < vector <int> > board(N, vector<int>(N));
    vector < vector <int> > goal(N, vector<int>(N));
    int value = 0;
    int count = 0;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            cin >> value;
            board.at(i).at(j) = value;
            goal.at(i).at(j) = count;
            count += 1;
        }
    }

    Node * init = new Node;
    init -> board = board;
    init -> g = 0;
    init -> h = get_h(*init, goal);
    init -> f = init -> g + init -> h;


    Node * solution = ida(board, goal, init);
    if (solution != nullptr)
    {
        stack <Node> mystack;
        while (solution -> link != nullptr)
        {
            mystack.push(*solution);
            solution = solution -> link;
        }
        cout << mystack.size() << endl;
        while (!mystack.empty())
        {
            *solution = mystack.top();
            mystack.pop();
            cout << solution -> move << endl;
        }

        display_board(*solution);
    }
    else
    {
        cout << "solution not found." << endl;
    }
    
}
