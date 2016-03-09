/*
 * Buffer.h
 *
 *  Created on: Nov 12, 2014
 *      Author: mude1013
 */


#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
public:
	Buffer();
	virtual ~Buffer();
	void read();
	char speicher[1024];
	char getSpeicher(int i);

};



#endif /* BUFFER_H_ */
