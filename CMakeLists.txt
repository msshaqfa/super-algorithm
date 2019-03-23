#%% ***********************************************************************%
#% All rights reserved � to the authors: Mahmoud SHAQFA and Zoltan ORBAN   %
#%                                                                         %
#% M. Shaqfa Contact:                                                      %
#% Earthquake Engineering and Structural Dynamics Laboratory (EESD),       %
#% School of Architecture, Civil and Environmental Engineering (ENAC),     %
#% Ecole polytechnique federale de Lausanne (EPFL),                        %
#% CH-1015 Lausanne, Switzerland.                                          %
#%               Tel.: +41 21 69 33297                                     %
#%               Email: mahmoud.shaqfa@epfl.ch                             %
#%                                                                         %
#% Z. ORBAN Contact:                                                       %
#% Department of Structural Engineering,                                   %
#% Faculty of Engineering and Information Technology,                      %
#% University of Pecs, Boszorkany u. 2,                                    %
#% H-7624 Pecs, Hungary.                                                   %
#%               Email: orbanz@mik.pte.hu                                  %
#%*************************************************************************%
#% - This code is just a simple demonstration for the modified algorithm   %
#%   without taking into account filtering the population(HM).             %
#% - This code is not optimized; should work faster with better            %
#%   implementations.                                                      %
#%*************************************************************************%
#% Main references for this paper and code:                                %
#%                                                                         %
#% [1] - Geem, Z.W.: Optimal cost design of water distribution             %
#%       networks usingharmony search 38, 259-277(2006)                    %
#%                                                                         %
#% [2] - Geem, Z.W.: Novel derivative of harmony search algorithm for      %
#%       discrete design variables. Applied Mathematics and Computation    %
#%       199(1), 223-230(2008). DOI https://doi.org/10.1016/j.amc.2007.    %
#%       09.049.                                                           %
#%                                                                         %
#% [3] - Geem, Z.W., Sim, K.B.: Parameter-setting-free harmony search      %
#%       algorithm 217, 3881-3889 (2010)                                   %
#%*************************************************************************%
#% This file is free: you can redistribute it and/or modify                %
#% it under the terms of the GNU General Public License as published by    %
#% the Free Software Foundation, either version 3 of the License, or       %
#% (at your option) any later version.                                     %
#%                                                                         %
#% This file is distributed in the hope that it will be useful,            %
#% but WITHOUT ANY WARRANTY; without even the implied warranty of          %
#% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           %
#% GNU General Public License for more details.                            %
#% TO recieve a copy of GNU License refer to: https://www.gnu.org/licenses/%
#%*************************************************************************%

cmake_minimum_required(VERSION 3.10)
project(ModifiedPSFHS)

set(CMAKE_CXX_STANDARD 14) # At least C++14

add_executable(ModifiedPSFHS main.cpp types.h population.cpp population.h randomness_generator.h MPSFHS.cpp
        MPSFHS.h objective.cpp objective.h vectorized_operations.h MPFHS_interface.cpp MPFHS_interface.h
        python_API.h write_CSV.cpp write_CSV.h write_VTK.cpp write_VTK.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plotter.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
