/*
 * Ereignis.h
 *
 *  Created on: 04.11.2014
 *      Author: jannis
 */

#ifndef EREIGNIS_H_
#define EREIGNIS_H_

/**
 * Die verschiedenen Tokentypen
 */
// geändert! FehlerToken -> FailToken und BezeichnerToken -> IdentifierToken 31.03.15
enum Tokentyp {PlusToken, MinusToken, MultiplyToken, DivideToken,
				ExclamationToken, AndToken, SemicolonToken,
				OpenBracketToken, CloseBracketToken, OpenCurlyToken,
				CloseCurlyToken, OpenSquareToken, CloseSquareToken,
				IdentifierToken, IntegerToken, SmallToken, BigToken,
				EqualsToken, SmallerDoubleBiggerToken, DoubleToken,
				DoubleEqualsToken, EmptyToken, FailToken, EndToken};


#endif /* EREIGNIS_H_ */
