#ifndef iScissor_H
#define iScissor_H

#include "imgflt.h"

const int INITIAL = 0;
const int ACTIVE = 1;
const int EXPANDED = 2;

// added by dewey
const double SQRT2 = 1.4142135623730950488016887242097;
const double SQINV = 1.0 / SQRT2;

// The eight filter kernels (Original)
///////////////////////////////////////////////////////////////////////
//
//		321
//		4 0
//		567
//
const double Akernels[8][9] = {
    {
        // 0
        0.0000, 0.2500, 0.2500 ,
        0.0000, 0.0000, 0.0000 ,
        0.0000, -0.250, -0.250
    },
    {
        // 1
        0.0000,  SQINV, 0.0000 ,
        0.0000, 0.0000, -SQINV ,
        0.0000, 0.0000, 0.0000
    },
    {
        // 2
        0.2500, 0.0000, -0.250 ,
        0.2500, 0.0000, -0.250 ,
        0.0000, 0.0000, 0.0000
    },
    {
        // 3
        0.0000,  SQINV, 0.0000 ,
        -SQINV, 0.0000, 0.0000 ,
        0.0000, 0.0000, 0.0000
    },
    {
        // 4
        0.2500, 0.2500, 0.0000 ,
        0.0000, 0.0000, 0.0000 ,
        -0.250, -0.250, 0.0000
    },
    {
        // 5
        0.0000, 0.0000, 0.0000 ,
         SQINV, 0.0000, 0.0000 ,
        0.0000, -SQINV, 0.0000
    },
    {
        // 6
        0.0000, 0.0000, 0.0000 ,
        0.2500, 0.0000, -0.250 ,
        0.2500, 0.0000, -0.250
    },
    {
        // 7
        0.0000, 0.0000, 0.0000 ,
        0.0000, 0.0000,  SQINV ,
        0.0000, -SQINV, 0.0000
    }
};

// The eight filter kernels (convolved with 3x3 averaging filter)
///////////////////////////////////////////////////////////////////////
//
//		321
//		4 0
//		567
//
const double Bkernels[8][25] = {
    {
        // 0
        0.00000, 0.02780, 0.05560, 0.05560, 0.02780 ,
        0.00000, 0.02780, 0.05560, 0.05560, 0.02780 ,
        0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, -0.0278, -0.0556, -0.0556, -0.0278 ,
        0.00000, -0.0278, -0.0556, -0.0556, -0.0278 
    },
    {
        // 1
        0.00000, 0.07860, 0.07860, 0.07860, 0.00000 ,
        0.00000, 0.07860, 0.00000, 0.00000, -0.0786 ,
        0.00000, 0.07860, 0.00000, 0.00000, -0.0786 ,
		0.00000, 0.00000, -0.0786, -0.0786, -0.0786 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 2
        0.02780, 0.02780, 0.00000, -0.0278, -0.0278 ,
        0.05560, 0.05560, 0.00000, -0.0556, -0.0556 ,
        0.05560, 0.05560, 0.00000, -0.0556, -0.0556 ,
        0.02780, 0.02780, 0.00000, -0.0278, -0.0278 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 3
        0.00000, 0.07860, 0.07860, 0.07860, 0.00000 ,
        -0.0786, 0.00000, 0.00000, 0.07860, 0.00000 ,
        -0.0786, 0.00000, 0.00000, 0.07860, 0.00000 ,
        -0.0786, -0.0786, -0.0786, 0.00000, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 4
		0.02780, 0.05560, 0.05560, 0.02780, 0.00000 ,
        0.02780, 0.05560, 0.05560, 0.02780, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
		-0.0278, -0.0556, -0.0556, -0.0278, 0.00000 ,
        -0.0278, -0.0556, -0.0556, -0.0278, 0.00000 
    },
    {
        // 5
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.07860, 0.07860, 0.07860, 0.00000, 0.00000 ,
		0.07860, 0.00000, 0.00000, -0.0786, 0.00000 ,
		0.07860, 0.00000, 0.00000, -0.0786, 0.00000 ,
		0.00000, -0.0786, -0.0786, -0.0786, 0.00000
    },
    {
        // 6
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.02780, 0.02780, 0.00000, -0.0278, -0.0278 ,
        0.05560, 0.05560, 0.00000, -0.0556, -0.0556 ,
        0.05560, 0.05560, 0.00000, -0.0556, -0.0556 ,
        0.02780, 0.02780, 0.00000, -0.0278, -0.0278
    },
    {
        // 7
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, 0.00000, 0.07860, 0.07860, 0.07860 ,
        0.00000, -0.0786, 0.00000, 0.00000, 0.07860 ,
        0.00000, -0.0786, 0.00000, 0.00000, 0.07860 ,
		0.00000, -0.0786, -0.0786, -0.0786, 0.00000
    }
};

// The eight filter kernels (convolved with 3x3 disk filter)
///////////////////////////////////////////////////////////////////////
//
//		321
//		4 0
//		567
//
const double Ckernels[8][25] = {
    {
        // 0
        0.00000, 0.00630, 0.04260, 0.04260, 0.00630 ,
        0.00000, 0.03630, 0.11590, 0.11590, 0.03630 ,
        0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, -0.0363, -0.1159, -0.1159, -0.0363 ,
        0.00000, -0.0063, -0.0426, -0.0426, -0.0063 
    },
    {
        // 1
        0.00000, 0.01770, 0.10280, 0.01770, 0.00000 ,
        0.00000, 0.10280, 0.20730, 0.00000, -0.0177 ,
        0.00000, 0.01770, 0.00000, -0.2073, -0.1028 ,
		0.00000, 0.00000, -0.0177, -0.1028, -0.0177 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 2
        0.00630, 0.03630, 0.00000, -0.0363, -0.0063 ,
        0.04260, 0.11590, 0.00000, -0.1159, -0.0426 ,
        0.04260, 0.11590, 0.00000, -0.1159, -0.0426 ,
        0.00630, 0.03630, 0.00000, -0.0363, -0.0063 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 3
        0.00000, 0.01770, 0.10280, 0.01770, 0.00000 ,
        -0.0177, 0.00000, 0.20730, 0.10280, 0.00000 ,
        -0.1028, -0.2073, 0.00000, 0.01770, 0.00000 ,
        -0.0177, -0.1028, -0.0177, 0.00000, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 4
		0.00630, 0.04260, 0.04260, 0.00630, 0.00000 ,
        0.03630, 0.11590, 0.11590, 0.03630, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
		-0.0363, -0.1159, -0.1159, -0.0363, 0.00000 ,
        -0.0063, -0.0426, -0.0426, -0.0063, 0.00000 
    },
    {
        // 5
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.01770, 0.10280, 0.01770, 0.00000, 0.00000 ,
		0.10280, 0.20730, 0.00000, -0.0177, 0.00000 ,
		0.01770, 0.00000, -0.2073, -0.1028, 0.00000 ,
		0.00000, -0.0177, -0.1028, -0.0177, 0.00000
    },
    {
        // 6
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00630, 0.03630, 0.00000, -0.0363, -0.0063 ,
        0.04260, 0.11590, 0.00000, -0.1159, -0.0426 ,
        0.04260, 0.11590, 0.00000, -0.1159, -0.0426 ,
        0.00630, 0.03630, 0.00000, -0.0363, -0.0063
    },
    {
        // 7
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, 0.00000, 0.01770, 0.10280, 0.01770 ,
        0.00000, -0.0177, 0.00000, 0.20730, 0.10280 ,
        0.00000, -0.1028, -0.2073, 0.00000, 0.01770 ,
		0.00000, -0.0177, -0.1028, -0.0177, 0.00000
    }
};

// The eight filter kernels (convolved with 3x3 gaussian filter, sigma = 0.5)
///////////////////////////////////////////////////////////////////////
//
//		321
//		4 0
//		567
//
const double Dkernels[8][25] = {
    {
        // 0
        0.00000, 0.00280, 0.02380, 0.02380, 0.00280 ,
        0.00000, 0.02100, 0.17580, 0.17580, 0.02100 ,
        0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, -0.0210, -0.1758, -0.1758, -0.0210 ,
        0.00000, -0.0028, -0.0238, -0.0238, -0.0028 
    },
    {
        // 1
        0.00000, 0.00800, 0.05930, 0.00800, 0.00000 ,
        0.00000, 0.05930, 0.42990, 0.00000, -0.0080 ,
        0.00000, 0.00800, 0.00000, -0.4299, -0.0593 ,
		0.00000, 0.00000, -0.0080, -0.0593, -0.0080 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 2
        0.00280, 0.02100, 0.00000, -0.0210, -0.0028 ,
        0.02380, 0.17580, 0.00000, -0.1758, -0.0238 ,
        0.02380, 0.17580, 0.00000, -0.1758, -0.0238 ,
        0.00280, 0.02100, 0.00000, -0.0210, -0.0028 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 3
        0.00000, 0.00800, 0.05930, 0.00800, 0.00000 ,
        -0.0080, 0.00000, 0.42990, 0.05930, 0.00000 ,
        -0.0593, -0.4299, 0.00000, 0.00800, 0.00000 ,
        -0.0080, -0.0593, -0.0080, 0.00000, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 
    },
    {
        // 4
		0.00280, 0.02380, 0.02380, 0.00280, 0.00000 ,
        0.02100, 0.17580, 0.17580, 0.02100, 0.00000 ,
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
		-0.0210, -0.1758, -0.1758, -0.0210, 0.00000 ,
        -0.0028, -0.0238, -0.0238, -0.0028, 0.00000 
    },
    {
        // 5
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00800, 0.05930, 0.00800, 0.00000, 0.00000 ,
		0.05930, 0.42990, 0.00000, -0.0080, 0.00000 ,
		0.00800, 0.00000, -0.4299, -0.0593, 0.00000 ,
		0.00000, -0.0080, -0.0593, -0.0080, 0.00000
    },
    {
        // 6
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00280, 0.02100, 0.00000, -0.0210, -0.0028 ,
        0.02380, 0.17580, 0.00000, -0.1758, -0.0238 ,
        0.02380, 0.17580, 0.00000, -0.1758, -0.0238 ,
        0.00280, 0.02100, 0.00000, -0.0210, -0.0028
    },
    {
        // 7
		0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
        0.00000, 0.00000, 0.00800, 0.05930, 0.00800 ,
        0.00000, -0.0080, 0.00000, 0.42990, 0.05930 ,
        0.00000, -0.0593, -0.4299, 0.00000, 0.00800 ,
		0.00000, -0.0080, -0.0593, -0.0080, 0.00000
    }
};

struct Node {
    //column and row:	remember the position of the node in original image so that its neighboring nodes can be located.
    //linkCost:			contains the costs of each link, as described in project page and in the SIGGRAPH95 paper.
    //state:			used to tag the node as being INITIAL, ACTIVE, or EXPANDED during the min-cost tree computation.
    //totalCost:		the minimum total cost from this node to the seed node.
    //prevNode:			points to its predecessor along the minimum cost path from the seed to that node.

    int column, row;
    double linkCost[8];
    int state;
    double totalCost;
    Node* prevNode;
	int pathLength;

    Node () {
        prevNode = NULL;
    }
    // this function helps to locate neighboring node in node buffer.
    void nbrNodeOffset(int& offsetX, int& offsetY, int linkIndex) {
        /*
         *  321
         *  4 0
         *  567
         */

        if (linkIndex == 0) {
            offsetX = 1;
            offsetY = 0;
        } else if (linkIndex == 1) {
            offsetX = 1;
            offsetY = -1;
        } else if (linkIndex == 2) {
            offsetX = 0;
            offsetY = -1;
        } else if (linkIndex == 3) {
            offsetX = -1;
            offsetY = -1;
        } else if (linkIndex == 4) {
            offsetX = -1;
            offsetY = 0;
        } else if (linkIndex == 5) {
            offsetX = -1;
            offsetY = 1;
        } else if (linkIndex == 6) {
            offsetX = 0;
            offsetY = 1;
        } else if (linkIndex == 7) {
            offsetX = 1;
            offsetY = 1;
        }
    }

    // used by the binary heap operation,
    // pqIndex is the index of this node in the heap.
    // you don't need to know about it to finish the assignment;

    int pqIndex;

    int& Index(void) {
        return pqIndex;
    }

    int Index(void) const {
        return pqIndex;
    }
};

inline int operator < (const Node& a, const Node& b)
{
    return a.totalCost < b.totalCost;
}

void InitNodeBuf(Node* nodes, const unsigned char* img, int width, int height);

double CrossCorrelate(const double filterKernel[3][3], const unsigned char* img, int imgWidth, int imgHeight, int x, int y, int c);

void LiveWireDP(int seedX, int seedY, Node* nodes, int width, int height, const unsigned char* selection, int expanded);

void MinimumPath(CTypedPtrDblList <Node>* path, int freePtX, int freePtY, Node* nodes, int width, int height);

void SeedSnap(int& x, int& y, unsigned char* img, int width, int height);

inline void DigitizeCost(unsigned char* cst, double lCost)
{
    cst[0] = cst[1] = cst[2] = (unsigned char)(floor(__max(0.0, __min(255.0, lCost))));
}

void MakeCostGraph(unsigned char* costGraph, const Node* nodes, const unsigned char* img, int width, int height);

//students don't need this data structure in assignment for the required work.
struct Seed {
    int x, y;
    int seed; //seed = 1, if it is a seed, otherwise, it is a ordinary contour location;

    Seed(int i, int j) {
        x = i;
        y = j;
    }
    Seed(int i, int j, int s) {
        x = i;
        y = j;
        seed = s;
    }
    Seed(void) {
    }
};

#endif
