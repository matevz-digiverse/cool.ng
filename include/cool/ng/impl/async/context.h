/* Copyright (c) 2017 Digiverse d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. The
 * license should be included in the source distribution of the Software;
 * if not, you may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * The above copyright notice and licensing terms shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#if !defined(cool_ng_41352af7_f2d7_4732_8200_beef75dc84b2)
#define      cool_ng_41352af7_f2d7_4732_8200_beef75dc84b2

#include <cstddef>
#include <memory>
#include <functional>

namespace cool { namespace ng {  namespace async {

class runner;

namespace detail {

// ---- execution context interface
class context
{
public:
  using exception_reporter = std::function<void(const std::exception_ptr&)>;

public:
  virtual ~context() { /* noop */ }

  // returns pointer to runner that is supposed to execute this context
  virtual std::weak_ptr<async::runner> get_runner() const = 0;
  // entry point to this context; to enter when context starts execute
  virtual void entry_point(const std::shared_ptr<async::runner>&, context*) = 0;
  // name of the context (context type name) for debugging purposes
  virtual const char* name() const = 0;
  // returns true if entry point will execute, false otherwise
  virtual bool will_execute() const = 0;
};

// ---- execution context stack interface
// ---- each run() call creates a new execution context stack which is then
// ---- (re)submitted to task queues as long as there are unfinished contexts
class context_stack
{
 public:
  virtual ~context_stack() { /* noop */ }
  // pushes new context to the top of the stack
  virtual void push(context*) = 0;
  // returns top of the stack
  virtual context* top() const = 0;
  // return the top of the stack and removes it from the stack
  virtual context* pop() = 0;
  // returns true if stack is empty
  virtual bool empty() const = 0;
};




} } } }// namespace

#endif