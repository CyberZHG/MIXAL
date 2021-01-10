import { expect, test } from 'vitest'
// @ts-ignore
import { runExample } from './utils.ts'

test('Program M. Find the maximum', () => {
    const results = runExample("1_3_2_M_Find_the_maximum")
    expect(results["A"]["int"]).eq(5)
})

test('Program P. Print table of 500 primes', () => {
    const results = runExample("1_3_2_P_Print_table_of_500_primes")
    expect(results["line-printer"][0]["values"]).eq("FIRST FIVE HUNDRED PRIMES                              ")
    expect(results["line-printer"][1]["values"]).eq("     0002 0233 0547 0877 1229 1597 1993 2371 2749 3187 ")
    expect(results["line-printer"][2]["values"]).eq("     0003 0239 0557 0881 1231 1601 1997 2377 2753 3191 ")
    expect(results["line-printer"][3]["values"]).eq("     0005 0241 0563 0883 1237 1607 1999 2381 2767 3203 ")
    expect(results["line-printer"][4]["values"]).eq("     0007 0251 0569 0887 1249 1609 2003 2383 2777 3209 ")
    expect(results["line-printer"][5]["values"]).eq("     0011 0257 0571 0907 1259 1613 2011 2389 2789 3217 ")
    expect(results["line-printer"][6]["values"]).eq("     0229 0541 0863 1223 1583 1987 2357 2741 3181 3571 ")
})

test('Program A. Multiply permutations in cycle', () => {
    const results = runExample("1_3_3_A_Multiply_permutations_in_cycle_form")
    expect(results["line-printer"]["values"]).eq("    (  A    D    G  )        (  C    E    B  )    ")
})

test('Program B. Same effects as A', () => {
    const results = runExample("1_3_3_B_Same_effect_as_A")
    expect(results["line-printer"]["values"]).eq("    (  C    E    B  )        (  D    G    A  )    ")
})

test('Program I. Inverse in space', () => {
    const results = runExample("1_3_3_I_Inverse_in_space")
    expect(results["memory"]["values"]).deep.eq([3, 2, 6, 5, 4, 1])
})

test('Program J. Analogous to program I', () => {
    const results = runExample("1_3_3_J_Analogous_to_program_I")
    expect(results["memory"]["values"]).deep.eq([3, 2, 6, 5, 4, 1])
})
