#ifndef __MIROS_H__
#define __MIROS_H__


/*Thread Control Block (TCB)*/
typedef struct {
	
	 void *sp; /*stack pointer*/
	 /* ... other attributes associated with a thread*/
} OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void);

/*this function must be called with interrupt DISABLED*/
void OS_sched(void);

void OSThread_start(
	 OSThread *me,
	 OSThreadHandler threadHandler,
	 void *stkSto, uint32_t stkSize);

#endif /*__MIROS_H__*/