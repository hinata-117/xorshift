use std::time::{Duration, Instant};

struct Xorshift32x1T {
    val: u32
}

/**
 * @brief 32bit変数1つだけで構成された xorshift 疑似乱数
 * @note 周期は (2**32) - 1
 * @note 初期値に 0 は使用しないこと
 * @note 初期値(引数)を 1 に選んだ時の乱数の推移
 *       270369, 67634689, 2647435461, 307599695, 2398689233
 * @note 参考: https://ja.wikipedia.org/wiki/Xorshift
 */
 /* ------------------------------------------------------------------------- */
 fn xorshift32x1_next(param: &mut Xorshift32x1T) -> u32 {
     param.val ^= param.val << 13;
     param.val ^= param.val >> 17;
     param.val ^= param.val << 5;
     param.val
 }

/**
 * @brief 疑似乱数の周期評価用関数
 * @note ただの評価用関数であり、運用で用いることは無い
 */
 /* ------------------------------------------------------------------------- */
 fn xorshift32x1_eval_period()
 {
     let mut test = Xorshift32x1T{val: 1};
     xorshift32x1_next(&mut test);
     let init: u32 = test.val;
     for _i in 1..5000000000u64 {
         let dummy = xorshift32x1_next(&mut test);
         if init == dummy {
             println!("equal at {}", _i);
         }
     }
 }

fn main() {
    println!("+++++++ start of program +++++++");
    let start = Instant::now();

    let mut xorshift = Xorshift32x1T{val: 1};
    for _i in 0..5 {
        xorshift32x1_next(&mut xorshift);
        print!("{},", xorshift.val);
    }
    println!("");
    xorshift32x1_eval_period();

    let end = start.elapsed();
    println!("+++++++ end of program({}.{:03}秒) +++++++\n", end.as_secs(), end.subsec_nanos() / 1_000_000);
}
