#!/usr/bin/python

class Employee:

   'Common base class for all employees'

   empCount = 0

   def __init__(self, name, salary, age, className):

      self.name = name

      self.salary = salary

      self.age = age

      self.className = className

      Employee.empCount += 1

  

   def displayCount(self):

     print "Total Employee %d" % Employee.empCount

 

   def displayEmployee(self):

      print "Name : ", self.name,  ", Salary: ", self.salary, ", Age: ", self.age, ", Name of class: ", self.className

 

"This would create first object of Employee class"

emp1 = Employee("Marlu", 2000, 27, "Object Oriented Programming")

"This would create second object of Employee class"

emp2 = Employee("Ashis", 5000, 78, "Generic Class Name 201")

emp1.displayEmployee()

emp2.displayEmployee()

print "Total Employee %d" % Employee.empCount