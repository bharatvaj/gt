#include <stdio.h>
#include <stddef.h>

/*
 * Generalized Object Notation Spec
 * A whitespace is space, linefeed, carriage return or horizontal tab.
 * An object is an unordered set of name/value pairs. An object begins with '{' and ends with '}'. Each name is followed by ':' and the name/value pairs are separated by (ws)+
 * A value can be a string in single quotes or a number or an object or an array. These structures can be nested.
 * A string is a sequence of zero or more Unicode character, wrapped in double quotes, using backslash escapes. A character is represented as a single character string.
 * A number is of regex (digit*)?\.?(digit*)?e?.-?digit*
 */

const char* return_string() {
	const char* str = "{ "
		"path: { "
			"d [ M150 0 L75 200 L225 200 Z ] "
		"} "
		"height: 210 width: 400"
	"}";
	return str;
}


short is_a_ws(const char* s, size_t pos) {
	return
		s[pos] == '\n'
		|| s[pos] == '\r'
		|| s[pos] == ' '
		|| s[pos] == '\t';
}

int main(int argc, char* argv[]) {
	const char* str = return_string();
	int i = 0;
	int start_pos = -1;
	int end_pos = -1;
	for (; str[i] != '\0'; i++) {
		if (
			(start_pos == -1 && end_pos == -1) // token mode check off
			&& ! is_a_ws(str, i) // not a whitespace
		   ) {
			start_pos = i; // token mode on
		} else if (start_pos != -1 && end_pos == -1) { // token parse
			if (is_a_ws(str, i)) { // a white space!
				end_pos = i; // conclude token mode
				// ======================
				// should be in callback
				fprintf(stderr, "Next token @ %d,%d: ", start_pos, end_pos);
				for (int j = start_pos; j < end_pos; j++) {
					fprintf(stderr, "%c", str[j]);
				}
				fprintf(stderr, "\n");
				// ======================
				// token mode off
				start_pos = -1;
				end_pos = -1;
			}
		}
	}
	return 0;
}
