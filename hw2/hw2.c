#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void IF();
void BLOCK();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tokens[tokenIdx]);
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}

int isEnd() {
  return tokenIdx >= tokenTop;
}

char *next() {
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    printf("skip(%s) got %s fail!\n", set, next());
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  // ... (existing code for F remains the same)
}

// E = F (op E)*
int E() {
  // ... (existing code for E remains the same)
}

// FOR = for (ASSIGN EXP; EXP) STMT

// ASSIGN = id '=' E;
void ASSIGN() {
  // ... (existing code for ASSIGN remains the same)
}

// WHILE = while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");
  int e = E();
  emit("if not T%d goto L%d\n", e, whileEnd);
  skip(")");
  STMT();
  emit("goto L%d\n", whileBegin);
  emit("(L%d)\n", whileEnd);
}

// if (EXP) STMT (else STMT)?
void IF() {
  skip("if");
  skip("(");
  E();
  skip(")");
  STMT();
  if (isNext("else")) {
    skip("else");
    STMT();
  }
}

// DOWHILE = do STMT while (E);
void DOWHILE() {
  int doBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", doBegin);
  skip("do");
  STMT();
  emit("(L%d)\n", whileEnd);  // Label for the end of the loop body
  skip("while");
  skip("(");
  int e = E();
  emit("if T%d goto L%d\n", e, doBegin);  // Jump back to the beginning if condition is true
  skip(")");
}

// STMT = WHILE | BLOCK | IF | DOWHILE | ASSIGN
void STMT() {
  if (isNext("while"))
    WHILE();
  else if (isNext("do"))
    DOWHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMTS }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMTS
void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}
