Gdrcoin Core integration/staging tree
=====================================

https://core.gdrcoin.org

What is Gdrcoin?
----------------

Gdrcoin is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. Gdrcoin uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Gdrcoin Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Gdrcoin Core software, see https://gdrcoin.org, or read the
[original whitepaper](https://core.gdrcoin.org/bitcoin.pdf) from which
Gdrcoin derived from.

License
-------

Gdrcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://gitlab.com/gdrcoin/gdrcoin/tags) are created
regularly to indicate new official, stable release versions of Gdrcoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://lists.linuxfoundation.org/mailman/listinfo/gdrcoin-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #gdrcoin-core-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
