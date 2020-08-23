/**
 * @file xorshift.c
 * @brief xorshift �ɂ��^�����������̎������ؗp�v���O����
 * @note �ЂƂ܂��� 32bit �� xorshift �̂ݎ����B���̎����͖���
 */
#include "stdint.h"
#include "stdio.h"
#include <time.h>

typedef struct {
    uint32_t val;
} xorshift32x1_t;

/**
 * @brief 32bit�ϐ�1�����ō\�����ꂽ xorshift �^������
 * @note ������ (2**32) - 1
 * @note �����l�� 0 �͎g�p���Ȃ�����
 * @note �����l(����)�� 1 �ɑI�񂾎��̗����̐���
 *       270369, 67634689, 2647435461, 307599695, 2398689233
 * @note �Q�l: https://ja.wikipedia.org/wiki/Xorshift
 */
 /* ------------------------------------------------------------------------- */
uint32_t Xorshift32x1_next(xorshift32x1_t* param)
{
    param->val = param->val ^ (param->val << 13);
    param->val = param->val ^ (param->val >> 17);
    return param->val = param->val ^ (param->val << 5);
}

/**
 * @brief �^�������̎����]���p�֐�
 * @note �����̕]���p�֐��ł���A�^�p�ŗp���邱�Ƃ͖���
 */
 /* ------------------------------------------------------------------------- */
void Xorshift32x1_eval_period(void)
{
    xorshift32x1_t test;
    test.val = 1;
    Xorshift32x1_next(&test);
    uint32_t init = test.val;
    uint32_t dummy = 0;
    for (uint64_t i = 1; i < 5000000000; i++) {
        dummy = Xorshift32x1_next(&test);
        if (init == dummy) {
            printf("equal at %llu\n", i);
        }
    }
    return;
}

/**
 * @brief ���C���֐�
 */
 /* ------------------------------------------------------------------------- */
void main()
{
    printf("+++++++ start of program +++++++\n");
    clock_t start, end;
    start = clock();

    xorshift32x1_t xorshift;
    xorshift.val = 1;
    for (uint8_t i = 0; i < 5; i++) {
        Xorshift32x1_next(&xorshift);
        printf("%u, ", xorshift.val);
    }
    printf("\n");
    Xorshift32x1_eval_period();

    end = clock();
    printf("+++++++ end of program(%.2f�b) +++++++\n", (double)(end - start) / CLOCKS_PER_SEC);
    return;
}
