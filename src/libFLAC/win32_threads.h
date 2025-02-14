#pragma once

#include <windows.h>

typedef SRWLOCK pthread_mutex_t;
typedef CONDITION_VARIABLE pthread_cond_t;
typedef HANDLE pthread_t;

typedef struct pthread_mutexattr_t pthread_mutexattr_t;
typedef struct pthread_condattr_t pthread_condattr_t;
typedef struct pthread_attr_t pthread_attr_t;

static int pthread_mutex_init(pthread_mutex_t* mtx, const pthread_mutexattr_t* attr)
{
	InitializeSRWLock(mtx);
	return 0;
}

static int pthread_mutex_destroy(pthread_mutex_t* mtx)
{
	return 0;
}

static int pthread_mutex_trylock(pthread_mutex_t* mtx)
{
	return TryAcquireSRWLockExclusive(mtx) == 0;
}

static int pthread_mutex_lock(pthread_mutex_t* mtx)
{
	AcquireSRWLockExclusive(mtx);
	return 0;
}

static int pthread_mutex_unlock(pthread_mutex_t* mtx)
{
	ReleaseSRWLockExclusive(mtx);
	return 0;
}

static int pthread_cond_init(pthread_cond_t* cnd, const pthread_condattr_t* attr)
{
	InitializeConditionVariable(cnd);
	return 0;
}

static int pthread_cond_destroy(pthread_cond_t* cnd)
{
	return 0;
}

static int pthread_cond_wait(pthread_cond_t* cnd, pthread_mutex_t* mtx)
{
	SleepConditionVariableSRW(cnd, mtx, INFINITE, 0);
	return 0;
}

static int pthread_cond_signal(pthread_cond_t* cnd)
{
	WakeConditionVariable(cnd);
	return 0;
}

static int pthread_cond_broadcast(pthread_cond_t* cnd)
{
	WakeAllConditionVariable(cnd);
	return 0;
}

static int pthread_join(pthread_t thread, void** value)
{
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	return 0;
}

static int pthread_create(pthread_t* thread, const pthread_attr_t* attr, DWORD (WINAPI *callback)(void*), void* arg)
{
	*thread = CreateThread(NULL, 0, callback, arg, 0, NULL);
	return 0;
}
