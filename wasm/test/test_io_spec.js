import { describe, it } from 'mocha';
import { expect } from 'chai';
import { executeWithSpec } from '../index.js';

const code = ' ORIG 3000\n HLT';

describe('IO Specs', () => {
    it('registerA | int', async () => {
        const spec = {"A": -3200};
        const results = executeWithSpec(code, spec);
        expect(results["A"]["int"]).to.equal(-3200);
    })
    it('registerA | text', async () => {
        const spec = {"A": "ABCDE"};
        const results = executeWithSpec(code, spec);
        expect(results["A"]["text"]).to.equal("ABCDE");
    })
    it('registerA | bytes', async () => {
        const spec = {"A": ["-", 1, 2, 3, 4, 25]};
        const results = executeWithSpec(code, spec);
        expect(results["A"]["bytes"]).to.equal("-  1  2  3  4 25");
    })
    it('registerA | bytes-merged-address', async () => {
        const spec = {"A": ["-", 2000, 3, 4, 25]};
        const results = executeWithSpec(code, spec);
        expect(results["A"]["bytes"]).to.equal("- 31 16  3  4 25");
    })
    it('registerX | int', async () => {
        const spec = {"X": -3200};
        const results = executeWithSpec(code, spec);
        expect(results["X"]["int"]).to.equal(-3200);
    })
    it('registerX | text', async () => {
        const spec = {"X": "ABCDE"};
        const results = executeWithSpec(code, spec);
        expect(results["X"]["text"]).to.equal("ABCDE");
    })
    it('registerX | bytes', async () => {
        const spec = {"X": ["-", 1, 2, 3, 4, 25]};
        const results = executeWithSpec(code, spec);
        expect(results["X"]["bytes"]).to.equal("-  1  2  3  4 25");
    })
    it('registerX | bytes-merged-address', async () => {
        const spec = {"X": ["-", 2000, 3, 4, 25]};
        const results = executeWithSpec(code, spec);
        expect(results["X"]["bytes"]).to.equal("- 31 16  3  4 25");
    })
    it('registerJ | int', async () => {
        const spec = {"J": -2000};
        const results = executeWithSpec(code, spec);
        expect(results["J"]["int"]).to.equal(-2000);
    })
    it('memory | int', async () => {
        const spec = {
            "memory": [{
                "offset": 2000,
                "values": [1, -2, 3],
            }],
            "outputs": {
                "memory": [{
                    "offset": 2000,
                    "length": 3,
                    "type": "int",
                }]
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"][0]["values"]).to.eql([1, -2, 3]);
    })
    it('memory | int | single', async () => {
        const spec = {
            "memory": {
                "offset": 2000,
                "values": [1, -2, 3],
            },
            "outputs": {
                "memory": {
                    "offset": 2000,
                    "length": 3,
                    "type": "int",
                }
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"]["values"]).to.eql([1, -2, 3]);
    })
    it('memory | int | single-output', async () => {
        const spec = {
            "memory": {
                "offset": 2000,
                "values": [1, -2, 3],
            },
            "outputs": {
                "memory": {
                    "offset": 2000,
                    "type": "int",
                }
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"]["value"]).to.eql(1);
    })
    it('memory | string', async () => {
        const spec = {
            "memory": [{
                "offset": 2000,
                "values": "ABCDEFGHIJ",
            }],
            "outputs": {
                "memory": [{
                    "offset": 2000,
                    "length": 2,
                    "type": "text",
                }]
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"][0]["values"]).to.equal("ABCDEFGHIJ");
    })
    it('memory | string-list', async () => {
        const spec = {
            "memory": [{
                "offset": 2000,
                "values": ["ABCDE", "FGHIJ"],
            }],
            "outputs": {
                "memory": [{
                    "offset": 2000,
                    "length": 2,
                    "type": "text",
                }]
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"][0]["values"]).to.equal("ABCDEFGHIJ");
    })
    it('memory | bytes', async () => {
        const spec = {
            "memory": [{
                "offset": 2000,
                "values": [["-", 1, 2, 3, 4, 25], ["-", 2000, 3, 4, 25]],
            }],
            "outputs": {
                "memory": [{
                    "offset": 2000,
                    "length": 2,
                    "type": "bytes",
                }]
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["memory"][0]["values"]).to.eql(['-  1  2  3  4 25', '- 31 16  3  4 25']);
    })
    it('card-reader | string', async () => {
        const spec = {
            "card-reader": [{
                "offset": 0,
                "values": "ABCDEFGHIJ",
            }],
            "outputs": {
                "card-reader": [{
                    "offset": 0,
                    "length": 2,
                    "type": "text",
                }]
            }
        };
        const results = executeWithSpec(code, spec);
        expect(results["card-reader"][0]["values"]).to.eql("ABCDEFGHIJ");
    })
})