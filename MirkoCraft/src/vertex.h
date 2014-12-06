#ifndef __VERTEX_H_
#define __VERTEX_H_

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct vertex3 {
	float x, y, z, rhw;
	DWORD col;
};

#endif // __VERTEX_H_
