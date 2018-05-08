# bs-tape

[BuckleScript][BuckleScript] bindings for [tape][tape].

There were already [bindings][bs-jest] for [jest][jest], but I find Jest to be pretty annoying to use, and a bit "too magical". So, I made this one.

Please be warned that I'm new to ReasonML / BuckleScript / OCaml, so there may be things herein that are non-idiomatic. PRs encouraged and welcomed!

## Getting Started

First, install the package:

```
yarn add --dev bs-tape
```

Then, add `bs-tape` to your `bs-dev-dependencies` in your `bsconfig.json`:

```javascript
{
  // ...
  "bs-dev-dependencies": [
    // ...
    "bs-tape"
  ],
  // ...
}
```

## License

ISC. See the [LICENSE](./LICENSE) file.

<!-- links -->
[BuckleScript]: https://bucklescript.github.io/
[tape]: https://github.com/substack/tape
[bs-jest]: https://github.com/glennsl/bs-jest
[jest]: https://github.com/facebook/jest