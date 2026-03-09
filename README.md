<!-- PROJECT HEADER -->

[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
![C](https://img.shields.io/badge/c-%2300599C.svg?logo=c&logoColor=white)

<!-- PROJECT EXPLANATION -->
## About the project

In this one, the goal is to solve a skyscraper puzzle, in which you have the clues and the application must fill in the board if possible.
The rules are simple:
* You must fill in the different squares on a board.
* Cells in the same row/column cannot contain a repeated value.
* Cells must respect the clues and all must be valid simultaneously for the puzzle to be completely solved.

## How it works?

It has a simple and organized schema.

### Main ([See main](main.c))
This part receives the arguments necessary to start solving the puzzle and creates the board.

It starts by checking whether the number of arguments is correct. In this case, it should only receive one, which will correspond to the clues.

If it is correct, a dynamic pointer is created to store the clues.

After checking that it is correct and that the memory has been allocated correctly, the values entered by the user are stored in the previously created pointer. ([see combination](combination.c))

Once the clues are obtained and the total number is verified to be correct (side length * 4 sides), the board is created with the dimensions indicated in the code.

Finally, the solving process begins, which is the last step and will determine whether the clues provided produce a solvable puzzle or not.

### Example of solvable puzzles:
* 4x4: "3 2 1 2 2 2 3 1 2 2 1 3 2 2 3 1"
* 5x5: "3 2 1 2 2 1 2 3 4 2 3 2 2 3 1 2 2 3 1 4"
* 6x6: "2 1 4 2 3 3 2 4 2 2 1 3 2 3 3 3 1 4 3 2 1 2 3 2"
* 7x7: "1 2 2 3 4 3 3 6 1 3 2 2 2 3 1 3 2 3 3 3 2 5 3 1 2 2 2 4"
* 8x8: "3 4 3 4 3 2 2 1 1 3 3 2 2 3 3 5 6 2 3 3 4 2 3 1 1 3 2 3 2 3 3 4"

### Board ([See board](board.c))
This file contains all the functions related to the initial creation of the board.

To begin with, it receives a board of the specified size and fills all the squares with -1, indicating that the cell has no content.
Finally, it indicates the initial values, which are useful for subsequently reducing the solution time and being able to count on true values.

The initial evaluation corresponds to minimum and maximum values, i.e., 1 and size.
* When clue value is 1, only one skyscraper can be seen from the position in which it is located, so the adjacent square on the board is set to the value of size.
* When the clue value is size, it is known that all skyscrapers can be seen from the position in which it is located, so you must fill in all values from 1 to size in the corresponding row or column, starting with the minimum in the cell adjacent to this clue.

#### Example:

<div style="display: flex; gap: 20px;">
	<table>
	<caption>Original</caption>
	<tr>
		<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
	</tr>
	<tr>
		<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
	</tr>
	<tr>
		<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
	</tr>
	<tr>
		<td>1</td><td></td><td></td><td></td><td></td><td>3</td>
	</tr>
	<tr>
		<td>3</td><td></td><td></td><td></td><td></td><td>1</td>
	</tr>
	<tr>
		<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
	</tr>
	</table>
	<table>
	<caption>Added initial values</caption>
	<tr>
		<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
	</tr>
	<tr>
		<td>2</td><td></td><td></td><td>4</td><td></td><td>2</td>
	</tr>
	<tr>
		<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
	</tr>
	<tr>
		<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
	</tr>
	<tr>
		<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
	</tr>
	<tr>
		<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
	</tr>
	</table>
</div>

### Resolution ([See solve](solve.c))
The solution is easy to explain, but very costly to implement.

The basics are:
1. Start with the first cell, at position 0.
2. Set the minimum value to be tested, i.e. 1.
3. Check that the row and column containing this new value do not already contain it, to avoid duplicates.
4. If there is no duplication, check whether the clue is still viable. <br>This is where it starts to get tricky:
   - The table is filled in from left to right and top to bottom, so the top and left clues must always have a value greater than or equal to the number of skyscrapers visible throughout the process.
   - To verify whether the right or bottom clue is correct, the entire row or column must have been filled in, as empty cells in between make it impossible to obtain a clear result.
5. If all tests are passed, it means that the value set in the position is valid, so recursively, the function calls itself but indicating that the new position is the next one.
6. If any test fails, it returns to the previous function, sets the field to -1, and increases the test value.

#### Ending the process.
The steps are repeated as many times as necessary until one of the following cases occurs:
1. The final position of the puzzle has been reached and it has been solved.
2. The maximum test case has been reached without finding a valid value, either because of the clues or because it is duplicated.

In the first case, the solved puzzle is printed and 0 is returned, indicating that the execution has been successfully completed.<br>
In the second case, it returns 1 and does not print anything on the screen. It is the main function that, when evaluating the output value, indicates that there was an error, which indicates that it is impossible to solve.

#### Following the last example:

#### <span id="tabla-1">Step 1 to 3</span>
<table>
  <tr>
    <td>
      <table>
        <caption>1</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>2</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td></td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>3</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>1</td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>

#### <span id="tabla-2">Step 4 to 6</span>
<table>
  <tr>
    <td>
      <table>
        <caption>4</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>2</td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>5</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>3</td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>6</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>4</td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>

#### <span id="tabla-3">Step 7 to 9</span>
<table>
  <tr>
    <td>
      <table>
        <caption id="tabla-7">7</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td></td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>8</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>9</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>1</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>

#### <span id="tabla-4">Step 10 to 12</span>
<table>
  <tr>
    <td>
      <table>
        <caption id="tabla-10">10</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>2</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>11</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td></td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>12</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td></td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>

#### <span id="tabla-5">Step 13 to 15</span>
<table>
  <tr>
    <td>
      <table>
        <caption id="tabla-10">13</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>1</td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>14</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>2</td><td></td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>15</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>1</td><td>2</td><td>1</td><td></td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td></td><td></td><td></td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td></td><td></td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>
<br><b><p> . . . </p></b><br>

#### <span id="tabla-6">Step 16 to 18</span>
<table>
  <tr>
    <td>
      <table>
        <caption id="tabla-10">16</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>3</td><td>4</td><td>1</td><td>2</td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td>2</td><td>3</td><td>1</td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td>1</td><td>3</td><td></td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>17</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>3</td><td>4</td><td>1</td><td>2</td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td>2</td><td>3</td><td>1</td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td>1</td><td>3</td><td>1</td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
    <td>
      <table>
        <caption>18</caption>
        <tr>
			<td></td><td>3</td><td>2</td><td>1</td><td>2</td><td></td>
		</tr>
		<tr>
			<td>2</td><td>2</td><td>1</td><td>4</td><td>3</td><td>2</td>
		</tr>
		<tr>
			<td>2</td><td>3</td><td>4</td><td>1</td><td>2</td><td>2</td>
		</tr>
		<tr>
			<td>1</td><td>4</td><td>2</td><td>3</td><td>1</td><td>3</td>
		</tr>
		<tr>
			<td>3</td><td>1</td><td>3</td><td>2</td><td>4</td><td>1</td>
		</tr>
		<tr>
			<td></td><td>2</td><td>2</td><td>3</td><td>1</td><td></td>
		</tr>
        </table>
    </td>
  </tr>
</table>

### Internal functioning

1. The function receives the board with original values derived from the strongest hints. [<sup>1</sup>](#tabla-1)
2. The algorithm attempts to place the minimum valid value **(1)** at the first available cell, **(0, 0)**. [<sup>2</sup>](#tabla-1)
3. Since **1** satisfies the row/column uniqueness and is consistent with the Top and Left hints, the recursion moves to the next cell. Adds **1** at the next available cell, **(0, 1)**. [<sup>3</sup>](#tabla-1)
4. At **(0, 1)**, placing **1** creates a duplicate in the row. The algorithm triggers a Backtrack: it resets the cell to **-1**, increments the test value, and tries **2** at position **(0, 1)**. [<sup>4</sup>](#tabla-2)
5. Although **2** is unique at **(0, 1)**, the "Left" hint **(e.g., 2)** is evaluated. The sequence 1, 2, 4 already shows **3** skyscrapers in [table 4](#tabla-2), the branch is discarded immediately **(prune)**.[<sup>5</sup>](#tabla-2)
6. Following the same logic, 1, 3, 4 shows **3** skyscrapers in [table 5](#tabla-2) when hint is **2**. The value is reset to **-1** and updated to **4** at **(0, 1)**. [<sup>6</sup>](#tabla-2)
7. It has tested **1 to 4** at position **(0, 1)** and none was valid, so it propagates back to position **(0, 0)**, replace value with **-1** and increments it to **2**, so now test **2** at position **(0, 0)**. [<sup>7</sup>](#tabla-3)
8. Value of **2** is valid at position **0** so passes to the next, adding **1** at position **(0, 1)**. [<sup>8</sup>](#tabla-3)
9. Upon reaching **(0, 2)**, the algorithm detects a pre-set value. It skips this position automatically, preserving the modification of the anchor, and jumps to the next available cell, adding **1** to position **(0, 3)**. [<sup>9</sup>](#tabla-3)
10. Value at **(0, 3)** is repeated so it tests **2** at this position. [<sup>10</sup>](#tabla-4)
11. Same as last step value of **2** is repeated so it changes to value **3** at position **(0, 3)**. [<sup>11</sup>](#tabla-4)

It follows the same steps over and over again till one of the [previous cases](#ending-the-process) are matched.

Tables 16 to 18 shows the last 3 steps where the program get to the end of the puzzle and all hints are validated, completing the puzzle solve.

There are two different ways to check hints, proactive and reactive.
- **Proactive**: when its checked with every cell when it's value changes, it's the case of Top and Left hints. As previously mentioned, the table is filled from left to right and from top to bottom so this hints are the guideline for a good solving.
- **Reactive**: it's only checked when the column/row is complete. It's the case of Right/Bottom hints, they are the final evaluation to ensure row/column follows the logic in both directions.

## Aditional features

The real reason for using malloc in this code is to be as scalable as possible, so that you can create boards as large as your computer allows.
However, there is a technical problem that can cause a bottleneck, as it follows a recursive resolution, so when you increase the size, the number of stacked iterations also increases, which could be a problem with large numbers. It could even use up all available memory and cause an exception. Keep in mind that the resolution time increases exponentially.
This could be a great opportunity to improve the code if desired, but it is functional in its current state.

## How to get your copy?

1. Clone the repository
   
First, clone the project using git:
```bash
	git clone https://github.com/agarciagalan/ResolutorRascacielos.git
	cd ResolutorRascacielos
```
<br>

2. Compilation

To compile the project using the standard 42 flags (-Wall -Wextra -Werror), run:
```bash
	cc -Wall -Werror -Wextra *.c -o rush01
```

**Tip**

If you want to debug the program in your console, you can add the -g flag at the end:

_cc -Wall -Werror -Wextra *.c -o rush01 -g_

<br>

3. Execution

The program receives a single string containing the clues for the puzzle. The number of clues must be size * 4 (e.g., 16 clues for a 4x4 board).

Examples can be found [here](#example-of-solvable-puzzles). <br>
The execution should be like shown:
```bash
	./rush01 "3 2 1 2 2 2 3 1 2 2 1 3 2 2 3 1"
```
<br>

## What is a rush?

A rush is a project that has a limited time frame for completion, running from Friday afternoon/evening until Sunday evening.

The positive side, although sometimes negative (depending on your luck), is that you have the help of two other team members with whom you must coordinate to carry out the necessary tasks so that the code compiles, complies with norminette, and is functional before the short period of time allowed ends.
Finally, you must defend your work, explaining what has been done in each part, why, and any possible improvements that may have occurred during development.

It is a very stressful process, but it allows you to step out of your comfort zone and work together with people of different levels of knowledge and expertise, this teach you many tricks and ways to programme more efficiently.

<!-- LINKS -->
[license-shield]: https://img.shields.io/badge/License-MIT-yellow.svg
[license-url]: LICENSE
[linkedin-shield]: https://img.shields.io/badge/linkedin-%230077B5.svg?logo=linkedin&logoColor=white
[linkedin-url]: https://www.linkedin.com/in/alejandro-garc%C3%ADa-gal%C3%A1n-495a09175/