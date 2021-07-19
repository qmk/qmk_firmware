/* Copyright (C) 2021 Islam Sharabash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Calculates the physical led positions and flags using a bazecor svg
// Open a bazecor layout with an svg and drop this code in the console
function compute() {

  const keys = Array.from(document.querySelectorAll('#keyshapes > *')).map((el) => ({el: el, type: 'key'}))
  const underglow = Array.from(document.querySelectorAll('#Areas > *')).map((el) => ({el: el, type: 'glow'}))

  let elements = keys.concat(underglow)

  elements.forEach((x) => {
    const box =  x.el.getBBox()
    x.x = box.x + (box.width / 2)
    x.y = box.y + (box.height / 2)
    x.box = box
    x.ledIndex =  parseInt(x.el.dataset.ledIndex, 10)
  })

  const minX = Math.min.apply(null, elements.map((x) => x.x))
  const maxX = Math.max.apply(null, elements.map((x) => x.x))
  const minY = Math.min.apply(null, elements.map((x) => x.y))
  const maxY = Math.max.apply(null, elements.map((x) => x.y))

  // we choose the smaller x or y scale so that aspect ratio is preserved
  const scale = Math.min(254 / (maxX - minX), 64 / (maxY - minY))

  // offset is for centering after scaling
  const offsetX = (254 - ((maxX - minX) * scale)) / 2
  const offsetY = (64 - ((maxY - minY) * scale)) / 2

  elements.forEach((x) => {
    // scale so it fits within 254x64, then offset to center, finally floor to
    // round
    x.normX = Math.floor(((x.x - minX) * scale) + offsetX)
    x.normY = Math.floor(((x.y - minY) * scale) + offsetY)
  })


  const positions = []
  const flags = []

  elements.forEach((x) => {
    positions[x.ledIndex] = [x.normX, x.normY]
    // assume glow if not key
    flags[x.ledIndex] = x.type === 'key' ? 4 : 2
  })

  return { elements, positions, flags}
}

function go() {
  const results = compute()
  const positions = results.positions.map((x) => `{${x[0]}, ${x[1]}}`).join(', ')
  const flags = results.flags.join(', ')

  console.log('positions')
  console.log(positions)
  console.log('flags')
  console.log(flags)
}

;(go())
